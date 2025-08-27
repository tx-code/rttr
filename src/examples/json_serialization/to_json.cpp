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
*************************************************************************************/

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

json to_json_recursively(const instance& obj);

/////////////////////////////////////////////////////////////////////////////////////////

json write_variant(const variant& var);

json write_atomic_types_to_json(const type& t, const variant& var)
{
    if (t.is_arithmetic())
    {
        if (t == type::get<bool>())
            return var.to_bool();
        else if (t == type::get<char>())
            return var.to_bool();
        else if (t == type::get<int8_t>())
            return var.to_int8();
        else if (t == type::get<int16_t>())
            return var.to_int16();
        else if (t == type::get<int32_t>())
            return var.to_int32();
        else if (t == type::get<int64_t>())
            return var.to_int64();
        else if (t == type::get<uint8_t>())
            return var.to_uint8();
        else if (t == type::get<uint16_t>())
            return var.to_uint16();
        else if (t == type::get<uint32_t>())
            return var.to_uint32();
        else if (t == type::get<uint64_t>())
            return var.to_uint64();
        else if (t == type::get<float>())
            return var.to_double();
        else if (t == type::get<double>())
            return var.to_double();

        return json{};
    }
    else if (t.is_enumeration())
    {
        bool ok = false;
        auto result = var.to_string(&ok);
        if (ok)
        {
            return var.to_string();
        }
        else
        {
            ok = false;
            auto value = var.to_uint64(&ok);
            if (ok)
                return value;
            else
                return nullptr;
        }
    }
    else if (t == type::get<std::string>())
    {
        return var.to_string();
    }

    return json{};
}

/////////////////////////////////////////////////////////////////////////////////////////

static json write_array(const variant_sequential_view& view)
{
    json array_json = json::array();
    for (const auto& item : view)
    {
        if (item.is_sequential_container())
        {
            array_json.push_back(write_array(item.create_sequential_view()));
        }
        else
        {
            variant wrapped_var = item.extract_wrapped_value();
            type value_type = wrapped_var.get_type();
            if (value_type.is_arithmetic() || value_type == type::get<std::string>() || value_type.is_enumeration())
            {
                array_json.push_back(write_atomic_types_to_json(value_type, wrapped_var));
            }
            else // object
            {
                array_json.push_back(to_json_recursively(wrapped_var));
            }
        }
    }
    return array_json;
}


/////////////////////////////////////////////////////////////////////////////////////////

static json write_associative_container(const variant_associative_view& view)
{
    static const string_view key_name("key");
    static const string_view value_name("value");

    json array_json = json::array();

    if (view.is_key_only_type())
    {
        for (auto& item : view)
        {
            array_json.push_back(write_variant(item.first));
        }
    }
    else
    {
        for (auto& item : view)
        {
            json obj_json = json::object();
            obj_json[key_name.data()] = write_variant(item.first);
            obj_json[value_name.data()] = write_variant(item.second);
            array_json.push_back(obj_json);
        }
    }

    return array_json;
}

/////////////////////////////////////////////////////////////////////////////////////////

json write_variant(const variant& var)
{
    auto value_type = var.get_type();
    auto wrapped_type = value_type.is_wrapper() ? value_type.get_wrapped_type() : value_type;
    bool is_wrapper = wrapped_type != value_type;

    // Try atomic types first
    auto atomic_result = write_atomic_types_to_json(is_wrapper ? wrapped_type : value_type,
                                                   is_wrapper ? var.extract_wrapped_value() : var);
    if (atomic_result.is_string() || atomic_result.is_number() || atomic_result.is_boolean() || atomic_result.is_null())
    {
        return atomic_result;
    }
    else if (var.is_sequential_container())
    {
        return write_array(var.create_sequential_view());
    }
    else if (var.is_associative_container())
    {
        return write_associative_container(var.create_associative_view());
    }
    else
    {
        auto child_props = is_wrapper ? wrapped_type.get_properties() : value_type.get_properties();
        if (!child_props.empty())
        {
            return to_json_recursively(var);
        }
        else
        {
            bool ok = false;
            auto text = var.to_string(&ok);
            if (ok)
            {
                return text;
            }
            return nullptr;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////

json to_json_recursively(const instance& obj2)
{
    json obj_json = json::object();
    instance obj = obj2.get_type().get_raw_type().is_wrapper() ? obj2.get_wrapped_instance() : obj2;

    auto prop_list = obj.get_derived_type().get_properties();
    for (auto prop : prop_list)
    {
        if (prop.get_metadata("NO_SERIALIZE"))
            continue;

        variant prop_value = prop.get_value(obj);
        if (!prop_value)
            continue; // cannot serialize, because we cannot retrieve the value

        const auto name = prop.get_name();
        try 
        {
            obj_json[name.data()] = write_variant(prop_value);
        }
        catch (const std::exception& e)
        {
            std::cerr << "cannot serialize property: " << name << " - " << e.what() << std::endl;
        }
    }

    return obj_json;
}

} // end namespace anonymous

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

namespace io
{

/////////////////////////////////////////////////////////////////////////////////////////

std::string to_json(rttr::instance obj)
{
    if (!obj.is_valid())
        return std::string();

    json result = to_json_recursively(obj);
    return result.dump(4); // Pretty print with 4 space indentation
}

/////////////////////////////////////////////////////////////////////////////////////////

} // end namespace io
