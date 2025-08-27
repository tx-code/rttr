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
#include <rttr/variant.h>

#include <nanobench.h>
#include <iostream>

struct MyCustomType
{
    int         m_data_i;
    bool        m_data_b;
    double      m_data_d;
    float       m_data_f;
    std::size_t m_data_st;
};


/////////////////////////////////////////////////////////////////////////////////////////

void bench_variant_empty_ctor()
{
    ankerl::nanobench::Bench().run("empty variant constructor", [&]() {
        rttr::variant var;
        ankerl::nanobench::doNotOptimizeAway(var);
    });
}

/////////////////////////////////////////////////////////////////////////////////////////

void bench_variant_void_ctor()
{
    ankerl::nanobench::Bench().run("void variant constructor", [&]() {
        rttr::variant var(rttr::detail::void_variant_type{});
        ankerl::nanobench::doNotOptimizeAway(var);
    });
}

/////////////////////////////////////////////////////////////////////////////////////////

void bench_variant_string_ctor()
{
    ankerl::nanobench::Bench().run("string variant constructor", [&]() {
        rttr::variant var(std::string("hello"));
        ankerl::nanobench::doNotOptimizeAway(var);
    });
}

/////////////////////////////////////////////////////////////////////////////////////////

void bench_variant_char_ctor()
{
    ankerl::nanobench::Bench().run("char variant constructor", [&]() {
        rttr::variant var("hello");
        ankerl::nanobench::doNotOptimizeAway(var);
    });
}

/////////////////////////////////////////////////////////////////////////////////////////

void bench_variant_float_ctor()
{
    ankerl::nanobench::Bench().run("float variant constructor", [&]() {
        rttr::variant var(42.0f);
        ankerl::nanobench::doNotOptimizeAway(var);
    });
}

/////////////////////////////////////////////////////////////////////////////////////////

void bench_variant_double_ctor()
{
    ankerl::nanobench::Bench().run("double variant constructor", [&]() {
        rttr::variant var(42.0);
        ankerl::nanobench::doNotOptimizeAway(var);
    });
}

/////////////////////////////////////////////////////////////////////////////////////////

void bench_variant_int_ctor()
{
    ankerl::nanobench::Bench().run("int variant constructor", [&]() {
        rttr::variant var(42);
        ankerl::nanobench::doNotOptimizeAway(var);
    });
}

/////////////////////////////////////////////////////////////////////////////////////////

void bench_variant_bool_ctor()
{
    ankerl::nanobench::Bench().run("bool variant constructor", [&]() {
        rttr::variant var(true);
        ankerl::nanobench::doNotOptimizeAway(var);
    });
}

/////////////////////////////////////////////////////////////////////////////////////////

void bench_variant_custom_ctor()
{
    ankerl::nanobench::Bench().run("custom type variant constructor", [&]() {
        rttr::variant var{MyCustomType{}};
        ankerl::nanobench::doNotOptimizeAway(var);
    });
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void bench_variant_empty_dtor()
{
    ankerl::nanobench::Bench().run("empty variant destructor", [&]() {
        auto var = std::make_unique<rttr::variant>();
        ankerl::nanobench::doNotOptimizeAway(var.get());
        var.reset();
    });
}

/////////////////////////////////////////////////////////////////////////////////////////

void bench_variant_void_dtor()
{
    ankerl::nanobench::Bench().run("void variant destructor", [&]() {
        auto var = std::make_unique<rttr::variant>(rttr::detail::void_variant_type{});
        ankerl::nanobench::doNotOptimizeAway(var.get());
        var.reset();
    });
}

/////////////////////////////////////////////////////////////////////////////////////////

void bench_variant_string_dtor()
{
    ankerl::nanobench::Bench().run("string variant destructor", [&]() {
        auto var = std::make_unique<rttr::variant>(std::string("hello"));
        ankerl::nanobench::doNotOptimizeAway(var.get());
        var.reset();
    });
}

/////////////////////////////////////////////////////////////////////////////////////////

void bench_variant_char_dtor()
{
    ankerl::nanobench::Bench().run("char variant destructor", [&]() {
        auto var = std::make_unique<rttr::variant>("hello");
        ankerl::nanobench::doNotOptimizeAway(var.get());
        var.reset();
    });
}

/////////////////////////////////////////////////////////////////////////////////////////

void bench_variant_float_dtor()
{
    ankerl::nanobench::Bench().run("float variant destructor", [&]() {
        auto var = std::make_unique<rttr::variant>(42.0f);
        ankerl::nanobench::doNotOptimizeAway(var.get());
        var.reset();
    });
}

/////////////////////////////////////////////////////////////////////////////////////////

void bench_variant_double_dtor()
{
    ankerl::nanobench::Bench().run("double variant destructor", [&]() {
        auto var = std::make_unique<rttr::variant>(42.0);
        ankerl::nanobench::doNotOptimizeAway(var.get());
        var.reset();
    });
}

/////////////////////////////////////////////////////////////////////////////////////////

void bench_variant_int_dtor()
{
    ankerl::nanobench::Bench().run("int variant destructor", [&]() {
        auto var = std::make_unique<rttr::variant>(static_cast<int>(42));
        ankerl::nanobench::doNotOptimizeAway(var.get());
        var.reset();
    });
}

/////////////////////////////////////////////////////////////////////////////////////////

void bench_variant_bool_dtor()
{
    ankerl::nanobench::Bench().run("bool variant destructor", [&]() {
        auto var = std::make_unique<rttr::variant>(true);
        ankerl::nanobench::doNotOptimizeAway(var.get());
        var.reset();
    });
}

/////////////////////////////////////////////////////////////////////////////////////////

void bench_variant_custom_dtor()
{
    ankerl::nanobench::Bench().run("custom type variant destructor", [&]() {
        auto var = std::make_unique<rttr::variant>(MyCustomType());
        ankerl::nanobench::doNotOptimizeAway(var.get());
        var.reset();
    });
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void bench_variant_create()
{
    std::cout << "\n=== RTTR Variant Creation Benchmarks ===\n" << std::endl;
    
    std::cout << "-- Constructor benchmarks --" << std::endl;
    bench_variant_empty_ctor();
    bench_variant_void_ctor();
    bench_variant_string_ctor();
    bench_variant_char_ctor();
    bench_variant_double_ctor();
    bench_variant_float_ctor();
    bench_variant_int_ctor();
    bench_variant_bool_ctor();
    bench_variant_custom_ctor();
    
    std::cout << "\n-- Destructor benchmarks --" << std::endl;
    bench_variant_empty_dtor();
    bench_variant_void_dtor();
    bench_variant_string_dtor();
    bench_variant_char_dtor();
    bench_variant_double_dtor();
    bench_variant_float_dtor();
    bench_variant_int_dtor();
    bench_variant_bool_dtor();
    bench_variant_custom_dtor();
}

/////////////////////////////////////////////////////////////////////////////////////////
