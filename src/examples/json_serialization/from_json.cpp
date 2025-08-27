/************************************************************************************
*                                                                                   *
*   Copyright (c) 2014 - 2018 Axel Menzel <info@rttr.org>                           *
*                                                                                   *
*   This file is part of RTTR (Run Time Type Reflection)                            *
*   License: MIT License                                                            *
*                                                                                   *
*   Permission is hereby granted, free of charge, to any person obtaining           *
*   a copy of this software and associated documentation files (the "Software"),    *
*   to deal in the Software without restriction, including without limitation       *
*   the rights to use, copy, modify, merge, publish, distribute, sublicense,        *
*   and/or sell copies of the Software, and to permit persons to whom the           *
*   Software is furnished to do so, subject to the following conditions:            *
*                                                                                   *
*   The above copyright notice and this permission notice shall be included in      *
*   all copies or substantial portions of the Software.                             *
*                                                                                   *
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR      *
*   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,        *
*   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE     *
*   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER          *
*   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,   *
*   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE   *
*   SOFTWARE.                                                                       *
*                                                                                   *
************************************************************************************/

#include <cstdio>
#include <string>
#include <vector>
#include <array>

#include <iostream>

#include <nlohmann/json.hpp>
#include <rttr/type>

using json = nlohmann::json;
using namespace rttr;

namespace
{

/////////////////////////////////////////////////////////////////////////////////////////

void fromjson_recursively(instance obj, const json& json_object);

/////////////////////////////////////////////////////////////////////////////////////////

variant extract_basic_types(const json& json_value)
{
    if (json_value.is_boolean())
        return json_value.get<bool>();
    else if (json_value.is_number_integer())
        return json_value.get<int64_t>();
    else if (json_value.is_number_unsigned()) 
        return json_value.get<uint64_t>();
    else if (json_value.is_number_float())
        return json_value.get<double>();
    else if (json_value.is_string())
        return json_value.get<std::string>();
    
    return variant();
}

/////////////////////////////////////////////////////////////////////////////////////////

static void write_array_recursively(variant_sequential_view& view, const json& json_array_value)
{
    view.set_size(json_array_value.size());
    const type array_value_type = view.get_value_type();

    for (size_t i = 0; i < json_array_value.size(); ++i)
    {
        auto& json_index_value = json_array_value[i];
        if (json_index_value.is_array())
        {
            auto sub_array_view = view.get_value(i).create_sequential_view();
            write_array_recursively(sub_array_view, json_index_value);
        }
        else if (json_index_value.is_object())
        {
            variant var_tmp = view.get_value(i);
            variant wrapped_var = var_tmp.extract_wrapped_value();
            fromjson_recursively(wrapped_var, json_index_value);
            view.set_value(i, wrapped_var);
        }
        else
        {
            variant extracted_value = extract_basic_types(json_index_value);
            if (extracted_value.convert(array_value_type))
                view.set_value(i, extracted_value);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////

variant extract_value(const json& json_value, const type& t)
{
    if (t.is_arithmetic())
    {
        if (t == type::get<bool>())
            return json_value.get<bool>();
        else if (t == type::get<char>())
            return static_cast<char>(json_value.get<int>());
        else if (t == type::get<int8_t>())
            return json_value.get<int8_t>();
        else if (t == type::get<int16_t>())
            return json_value.get<int16_t>();
        else if (t == type::get<int32_t>())
            return json_value.get<int32_t>();
        else if (t == type::get<int64_t>())
            return json_value.get<int64_t>();
        else if (t == type::get<uint8_t>())
            return json_value.get<uint8_t>();
        else if (t == type::get<uint16_t>())
            return json_value.get<uint16_t>();
        else if (t == type::get<uint32_t>())
            return json_value.get<uint32_t>();
        else if (t == type::get<uint64_t>())
            return json_value.get<uint64_t>();
        else if (t == type::get<float>())
            return json_value.get<float>();
        else if (t == type::get<double>())
            return json_value.get<double>();
    }
    else if (t.is_enumeration())
    {
        if (json_value.is_string())
        {
            return t.get_enumeration().name_to_value(json_value.get<std::string>());
        }
        else if (json_value.is_number_integer())
        {
            return t.get_enumeration().value_to_name(json_value.get<int64_t>());
        }
    }
    else if (t == type::get<std::string>())
    {
        return json_value.get<std::string>();
    }

    return variant();
}

/////////////////////////////////////////////////////////////////////////////////////////

void fromjson_recursively(instance obj, const json& json_object)
{
    instance wrapped_obj = obj.get_type().get_raw_type().is_wrapper() ? obj.get_wrapped_instance() : obj;
    const auto prop_list = wrapped_obj.get_derived_type().get_properties();

    for (auto prop : prop_list)
    {
        if (prop.get_metadata("NO_SERIALIZE"))
            continue;

        const auto name = prop.get_name();
        if (!json_object.contains(name.data()))
            continue;

        const json& json_value = json_object[name.data()];
        const type value_t = prop.get_type();

        switch (json_value.type())
        {
            case json::value_t::array:
            {
                variant var;
                if (value_t.is_sequential_container())
                {
                    var = prop.get_value(wrapped_obj);
                    auto view = var.create_sequential_view();
                    write_array_recursively(view, json_value);
                }
                break;
            }
            case json::value_t::object:
            {
                variant var = prop.get_value(wrapped_obj);
                fromjson_recursively(var, json_value);
                prop.set_value(wrapped_obj, var);
                break;
            }
            default:
            {
                variant extracted_value = extract_value(json_value, value_t.is_wrapper() ? value_t.get_wrapped_type() : value_t);
                if (extracted_value.convert(value_t))
                {
                    prop.set_value(wrapped_obj, extracted_value);
                }
            }
        }
    }
}

} // end namespace anonymous

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

namespace io
{

/////////////////////////////////////////////////////////////////////////////////////////

bool from_json(const std::string& json_str, rttr::instance obj)
{
    try 
    {
        json json_object = json::parse(json_str);
        fromjson_recursively(obj, json_object);
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << "JSON parsing error: " << e.what() << std::endl;
        return false;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////

} // end namespace io