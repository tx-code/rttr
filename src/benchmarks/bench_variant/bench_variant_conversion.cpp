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

#include <rttr/type>
#include <rttr/registration>

#include <nanobench.h>

#include <iostream>
#include <locale>

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

static int setup_integer()
{
    return 12345;
}

/////////////////////////////////////////////////////////////////////////////////////////

static float setup_float()
{
    return 123.12345f;
}

/////////////////////////////////////////////////////////////////////////////////////////

static double setup_double()
{
    return 123456.123456;
}

/////////////////////////////////////////////////////////////////////////////////////////

static bool setup_bool()
{
    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////

static std::string setup_string_integer()
{
    return std::string("12345");
}

/////////////////////////////////////////////////////////////////////////////////////////

static std::string setup_string_float()
{
    return std::string("123.12345");
}

/////////////////////////////////////////////////////////////////////////////////////////

static std::string setup_string_double()
{
    return std::string("123456.123456");
}

/////////////////////////////////////////////////////////////////////////////////////////

static std::string setup_string_bool()
{
    return std::string("1");
}


/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void bench_native_int_to_string()
{
    int var = setup_integer();
    ankerl::nanobench::Bench().run("native int to string", [&]() {
        std::string result = std::to_string(var);
        ankerl::nanobench::doNotOptimizeAway(result);
    });
}

/////////////////////////////////////////////////////////////////////////////////////////

void bench_variant_int_to_string()
{
    rttr::variant var = setup_integer();
    ankerl::nanobench::Bench().run("variant int to string", [&]() {
        std::string result = var.to_string();
        ankerl::nanobench::doNotOptimizeAway(result);
    });
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void bench_native_string_to_int()
{
    std::string number_string = setup_string_integer();
    ankerl::nanobench::Bench().run("native string to int", [&]() {
        std::size_t pos = 0;
        int result = std::stoi(number_string, &pos);
        ankerl::nanobench::doNotOptimizeAway(result);
    });
}

/////////////////////////////////////////////////////////////////////////////////////////

void bench_variant_string_to_int()
{
    rttr::variant var = setup_string_integer();
    ankerl::nanobench::Bench().run("variant string to int", [&]() {
        int result = var.to_int();
        ankerl::nanobench::doNotOptimizeAway(result);
    });
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void bench_native_float_to_string()
{
    float var = setup_float();
    ankerl::nanobench::Bench().run("native float to string", [&]() {
        std::string result = std::to_string(var);
        ankerl::nanobench::doNotOptimizeAway(result);
    });
}

/////////////////////////////////////////////////////////////////////////////////////////

void bench_variant_float_to_string()
{
    rttr::variant var = setup_float();
    ankerl::nanobench::Bench().run("variant float to string", [&]() {
        std::string result = var.to_string();
        ankerl::nanobench::doNotOptimizeAway(result);
    });
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void bench_native_string_to_float()
{
    std::string number_string = setup_string_float();
    ankerl::nanobench::Bench().run("native string to float", [&]() {
        std::size_t pos = 0;
        float result = std::stof(number_string, &pos);
        ankerl::nanobench::doNotOptimizeAway(result);
    });
}

/////////////////////////////////////////////////////////////////////////////////////////

void bench_variant_string_to_float()
{
    rttr::variant var = setup_string_float();
    ankerl::nanobench::Bench().run("variant string to float", [&]() {
        float result = var.to_float();
        ankerl::nanobench::doNotOptimizeAway(result);
    });
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void bench_native_double_to_string()
{
    double var = setup_double();
    ankerl::nanobench::Bench().run("native double to string", [&]() {
        std::string result = std::to_string(var);
        ankerl::nanobench::doNotOptimizeAway(result);
    });
}

/////////////////////////////////////////////////////////////////////////////////////////

void bench_variant_double_to_string()
{
    rttr::variant var = setup_double();
    ankerl::nanobench::Bench().run("variant double to string", [&]() {
        std::string result = var.to_string();
        ankerl::nanobench::doNotOptimizeAway(result);
    });
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void bench_native_string_to_double()
{
    std::string number_string = setup_string_double();
    ankerl::nanobench::Bench().run("native string to double", [&]() {
        std::size_t pos = 0;
        double result = std::stod(number_string, &pos);
        ankerl::nanobench::doNotOptimizeAway(result);
    });
}

/////////////////////////////////////////////////////////////////////////////////////////

void bench_variant_string_to_double()
{
    rttr::variant var = setup_string_double();
    ankerl::nanobench::Bench().run("variant string to double", [&]() {
        double result = var.to_double();
        ankerl::nanobench::doNotOptimizeAway(result);
    });
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void bench_native_bool_to_string()
{
    bool value = setup_bool();
    ankerl::nanobench::Bench().run("native bool to string", [&]() {
        std::string result = value ? std::string("true") : std::string("false");
        ankerl::nanobench::doNotOptimizeAway(result);
    });
}

/////////////////////////////////////////////////////////////////////////////////////////

void bench_variant_bool_to_string()
{
    rttr::variant var = setup_bool();
    ankerl::nanobench::Bench().run("variant bool to string", [&]() {
        std::string result = var.to_string();
        ankerl::nanobench::doNotOptimizeAway(result);
    });
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

static bool string_to_bool(std::string text)
{
    std::transform(text.cbegin(), text.cend(), text.begin(), ::tolower);
    text.erase( std::remove_if( text.begin(), text.end(), []( char ch ) { return std::isspace<char>( ch, std::locale::classic() ); } ), text.end() );

    return !(text == "false" || text == "0" || text.empty());
}

/////////////////////////////////////////////////////////////////////////////////////////

void bench_native_string_to_bool()
{
    std::string bool_string = setup_string_bool();
    ankerl::nanobench::Bench().run("native string to bool", [&]() {
        bool result = string_to_bool(bool_string);
        ankerl::nanobench::doNotOptimizeAway(result);
    });
}

/////////////////////////////////////////////////////////////////////////////////////////

void bench_variant_string_to_bool()
{
    rttr::variant var = setup_string_bool();
    ankerl::nanobench::Bench().run("variant string to bool", [&]() {
        bool result = var.to_bool();
        ankerl::nanobench::doNotOptimizeAway(result);
    });
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void bench_variant_conversion()
{
    std::cout << "\n=== RTTR Variant Conversion Benchmarks ===\n" << std::endl;
    
    std::cout << "-- int to string conversion --" << std::endl;
    bench_native_int_to_string();
    bench_variant_int_to_string();
    
    std::cout << "\n-- string to int conversion --" << std::endl;
    bench_native_string_to_int();
    bench_variant_string_to_int();
    
    std::cout << "\n-- float to string conversion --" << std::endl;
    bench_native_float_to_string();
    bench_variant_float_to_string();
    
    std::cout << "\n-- string to float conversion --" << std::endl;
    bench_native_string_to_float();
    bench_variant_string_to_float();
    
    std::cout << "\n-- double to string conversion --" << std::endl;
    bench_native_double_to_string();
    bench_variant_double_to_string();
    
    std::cout << "\n-- string to double conversion --" << std::endl;
    bench_native_string_to_double();
    bench_variant_string_to_double();
    
    std::cout << "\n-- bool to string conversion --" << std::endl;
    bench_native_bool_to_string();
    bench_variant_bool_to_string();
    
    std::cout << "\n-- string to bool conversion --" << std::endl;
    bench_native_string_to_bool();
    bench_variant_string_to_bool();
}

/////////////////////////////////////////////////////////////////////////////////////////
