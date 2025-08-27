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

#include "benchmarks/bench_method/test_methods.h"

#include <rttr/type>

#include <nanobench.h>
#include <iostream>


/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void bench_native_find_method_level_1()
{
    ns_foo::method_class_d_1 obj_1;
    ns_foo::method_class& obj_base = obj_1;
    volatile std::size_t value = 0;
    
    ankerl::nanobench::Bench().run("native find method level 1", [&]() {
        if (dynamic_cast<ns_foo::method_class_d_1*>(&obj_base))
        {
            value = 1;
        }
        ankerl::nanobench::doNotOptimizeAway(static_cast<std::size_t>(value));
    });
}

/////////////////////////////////////////////////////////////////////////////////////////

void bench_rttr_find_method_level_1()
{
    ns_foo::method_class_d_1 obj_1;
    ns_foo::method_class& obj_base = obj_1;
    volatile std::size_t value = 0;
    rttr::method m = rttr::type::get(nullptr).get_method("");
    
    ankerl::nanobench::Bench().run("rttr find method level 1", [&]() {
        if ((m = rttr::type::get(obj_base).get_method("method_1")))
        {
            value = 1;
        }
        ankerl::nanobench::doNotOptimizeAway(static_cast<std::size_t>(value));
    });
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void bench_native_find_method_level_3()
{
    ns_foo::method_class_d_3 obj_3;
    ns_foo::method_class& obj_base = obj_3;
    volatile std::size_t value = 0;
    
    ankerl::nanobench::Bench().run("native find method level 3", [&]() {
        if (dynamic_cast<ns_foo::method_class_d_3*>(&obj_base))
        {
            value = 1;
        }
        ankerl::nanobench::doNotOptimizeAway(static_cast<std::size_t>(value));
    });
}

/////////////////////////////////////////////////////////////////////////////////////////

void bench_rttr_find_method_level_3()
{
    ns_foo::method_class_d_3 obj_3;
    ns_foo::method_class& obj_base = obj_3;
    volatile std::size_t value = 0;
    rttr::method m = rttr::type::get(nullptr).get_method("");
    
    ankerl::nanobench::Bench().run("rttr find method level 3", [&]() {
        if ((m = rttr::type::get(obj_base).get_method("method_3")))
        {
            value = 1;
        }
        ankerl::nanobench::doNotOptimizeAway(static_cast<std::size_t>(value));
    });
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void bench_native_find_method_level_6()
{
    ns_foo::method_class_d_6 obj_6;
    ns_foo::method_class& obj_base = obj_6;
    volatile std::size_t value = 0;
    
    ankerl::nanobench::Bench().run("native find method level 6", [&]() {
        if (dynamic_cast<ns_foo::method_class_d_6*>(&obj_base))
        {
            value = 1;
        }
        ankerl::nanobench::doNotOptimizeAway(static_cast<std::size_t>(value));
    });
}

/////////////////////////////////////////////////////////////////////////////////////////

void bench_rttr_find_method_level_6()
{
    ns_foo::method_class_d_6 obj_6;
    ns_foo::method_class& obj_base = obj_6;
    volatile std::size_t value = 0;
    rttr::method m = rttr::type::get(nullptr).get_method("");
    
    ankerl::nanobench::Bench().run("rttr find method level 6", [&]() {
        if ((m = rttr::type::get(obj_base).get_method("method_6")))
        {
            value = 1;
        }
        ankerl::nanobench::doNotOptimizeAway(static_cast<std::size_t>(value));
    });
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////


void bench_native_find_method_neg_level_1()
{
    ns_foo::method_class_d_1 obj_1;
    ns_foo::method_class& obj_base = obj_1;
    volatile std::size_t value = 0;
    
    ankerl::nanobench::Bench().run("native find method neg level 1", [&]() {
        if (dynamic_cast<ns_foo::method_class_d_2*>(&obj_base))
        {
            value = 1;
        }
        ankerl::nanobench::doNotOptimizeAway(static_cast<std::size_t>(value));
    });
}

/////////////////////////////////////////////////////////////////////////////////////////

void bench_rttr_find_method_neg_level_1()
{
    ns_foo::method_class_d_1 obj_1;
    ns_foo::method_class& obj_base = obj_1;
    volatile std::size_t value = 0;
    rttr::method m = rttr::type::get(nullptr).get_method("");
    
    ankerl::nanobench::Bench().run("rttr find method neg level 1", [&]() {
        if ((m = rttr::type::get(obj_base).get_method("method_2")))
        {
            value = 1;
        }
        ankerl::nanobench::doNotOptimizeAway(static_cast<std::size_t>(value));
    });
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void bench_native_find_method_neg_level_3()
{
    ns_foo::method_class_d_3 obj_3;
    ns_foo::method_class& obj_base = obj_3;
    volatile std::size_t value = 0;
    
    ankerl::nanobench::Bench().run("native find method neg level 3", [&]() {
        if (dynamic_cast<ns_foo::method_class_d_4*>(&obj_base))
        {
            value = 1;
        }
        ankerl::nanobench::doNotOptimizeAway(static_cast<std::size_t>(value));
    });
}

/////////////////////////////////////////////////////////////////////////////////////////

void bench_rttr_find_method_neg_level_3()
{
    ns_foo::method_class_d_3 obj_3;
    ns_foo::method_class& obj_base = obj_3;
    volatile std::size_t value = 0;
    rttr::method m = rttr::type::get(nullptr).get_method("");
    
    ankerl::nanobench::Bench().run("rttr find method neg level 3", [&]() {
        if ((m = rttr::type::get(obj_base).get_method("method_4")))
        {
            value = 1;
        }
        ankerl::nanobench::doNotOptimizeAway(static_cast<std::size_t>(value));
    });
}


/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void bench_native_find_method_neg_level_6()
{
    ns_foo::method_class_d_6 obj_6;
    ns_foo::method_class& obj_base = obj_6;
    volatile std::size_t value = 0;
    
    ankerl::nanobench::Bench().run("native find method neg level 6", [&]() {
        if (dynamic_cast<ns_foo::method_class_d_7*>(&obj_base))
        {
            value = 1;
        }
        ankerl::nanobench::doNotOptimizeAway(static_cast<std::size_t>(value));
    });
}

/////////////////////////////////////////////////////////////////////////////////////////

void bench_rttr_find_method_neg_level_6()
{
    ns_foo::method_class_d_6 obj_6;
    ns_foo::method_class& obj_base = obj_6;
    volatile std::size_t value = 0;
    rttr::method m = rttr::type::get(nullptr).get_method("");
    
    ankerl::nanobench::Bench().run("rttr find method neg level 6", [&]() {
        if ((m = rttr::type::get(obj_base).get_method("method_7")))
        {
            value = 1;
        }
        ankerl::nanobench::doNotOptimizeAway(static_cast<std::size_t>(value));
    });
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void bench_native_find_method_cross_cast_level_1()
{
    ns_foo::class_multiple_final obj_final;
    ns_foo::class_multiple_base_A& obj_base = obj_final;
    volatile std::size_t value = 0;
    
    ankerl::nanobench::Bench().run("native find method cross cast level 1", [&]() {
        if (dynamic_cast<ns_foo::class_multiple_1C*>(&obj_base))
        {
            value = 1;
        }
        ankerl::nanobench::doNotOptimizeAway(static_cast<std::size_t>(value));
    });
}

/////////////////////////////////////////////////////////////////////////////////////////

void bench_rttr_find_method_cross_cast_level_1()
{
    ns_foo::class_multiple_final obj_final;
    ns_foo::class_multiple_base_A& obj_base = obj_final;
    volatile std::size_t value = 0;
    rttr::method m = rttr::type::get(nullptr).get_method("");
    
    ankerl::nanobench::Bench().run("rttr find method cross cast level 1", [&]() {
        if ((m = rttr::type::get(obj_base).get_method("method_13"))) //method 13 is contained in 'class_multiple_1C'
        {
            value = 1;
        }
        ankerl::nanobench::doNotOptimizeAway(static_cast<std::size_t>(value));
    });
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void bench_native_find_method_cross_cast_level_3()
{
    ns_foo::class_multiple_final obj_final;
    ns_foo::class_multiple_base_A& obj_base = obj_final;
    volatile std::size_t value = 0;
    
    ankerl::nanobench::Bench().run("native find method cross cast level 3", [&]() {
        if (dynamic_cast<ns_foo::class_multiple_3C*>(&obj_base))
        {
            value = 1;
        }
        ankerl::nanobench::doNotOptimizeAway(static_cast<std::size_t>(value));
    });
}

/////////////////////////////////////////////////////////////////////////////////////////

void bench_rttr_find_method_cross_cast_level_3()
{
    ns_foo::class_multiple_final obj_final;
    ns_foo::class_multiple_base_A& obj_base = obj_final;
    volatile std::size_t value = 0;
    rttr::method m = rttr::type::get(nullptr).get_method("");
    
    ankerl::nanobench::Bench().run("rttr find method cross cast level 3", [&]() {
        if ((m = rttr::type::get(obj_base).get_method("method_15"))) //method 15 is contained in 'class_multiple_3C'
        {
            value = 1;
        }
        ankerl::nanobench::doNotOptimizeAway(static_cast<std::size_t>(value));
    });
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void bench_native_find_method_cross_cast_level_6()
{
    ns_foo::class_multiple_final obj_final;
    ns_foo::class_multiple_base_C& obj_base = obj_final;
    volatile std::size_t value = 0;
    
    ankerl::nanobench::Bench().run("native find method cross cast level 6", [&]() {
        if (dynamic_cast<ns_foo::class_multiple_final*>(&obj_base))
        {
            value = 1;
        }
        ankerl::nanobench::doNotOptimizeAway(static_cast<std::size_t>(value));
    });
}

/////////////////////////////////////////////////////////////////////////////////////////

void bench_rttr_find_method_cross_cast_level_6()
{
    ns_foo::class_multiple_final obj_final;
    ns_foo::class_multiple_base_C& obj_base = obj_final;
    volatile std::size_t value = 0;
    rttr::method m = rttr::type::get(nullptr).get_method("");
    
    ankerl::nanobench::Bench().run("rttr find method cross cast level 6", [&]() {
        if ((m = rttr::type::get(obj_base).get_method("method_18"))) //method 18 is contained in 'class_multiple_final'
        {
            value = 1;
        }
        ankerl::nanobench::doNotOptimizeAway(static_cast<std::size_t>(value));
    });
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////


void bench_native_find_method_cross_cast_neg_level_1()
{
    ns_foo::class_multiple_2A obj_final;
    ns_foo::class_multiple_base_A& obj_base = obj_final;
    volatile std::size_t value = 0;
    
    ankerl::nanobench::Bench().run("native find method cross cast neg level 1", [&]() {
        if (dynamic_cast<ns_foo::class_multiple_1C*>(&obj_base))
        {
            value = 1;
        }
        ankerl::nanobench::doNotOptimizeAway(static_cast<std::size_t>(value));
    });
}

/////////////////////////////////////////////////////////////////////////////////////////

void bench_rttr_find_method_cross_cast_neg_level_1()
{
    ns_foo::class_multiple_2A obj_final;
    ns_foo::class_multiple_base_A& obj_base = obj_final;
    volatile std::size_t value = 0;
    rttr::method m = rttr::type::get(nullptr).get_method("");
    
    ankerl::nanobench::Bench().run("rttr find method cross cast neg level 1", [&]() {
        if ((m = rttr::type::get(obj_base).get_method("method_13"))) //method 13 is contained in 'class_multiple_1C'
        {
            value = 1;
        }
        ankerl::nanobench::doNotOptimizeAway(static_cast<std::size_t>(value));
    });
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void bench_native_find_method_cross_cast_neg_level_3()
{
    ns_foo::class_multiple_3A obj_final;
    ns_foo::class_multiple_base_A& obj_base = obj_final;
    volatile std::size_t value = 0;
    
    ankerl::nanobench::Bench().run("native find method cross cast neg level 3", [&]() {
        if (dynamic_cast<ns_foo::class_multiple_3C*>(&obj_base))
        {
            value = 1;
        }
        ankerl::nanobench::doNotOptimizeAway(static_cast<std::size_t>(value));
    });
}

/////////////////////////////////////////////////////////////////////////////////////////

void bench_rttr_find_method_cross_cast_neg_level_3()
{
    ns_foo::class_multiple_3A obj_final;
    ns_foo::class_multiple_base_A& obj_base = obj_final;
    volatile std::size_t value = 0;
    rttr::method m = rttr::type::get(nullptr).get_method("");
    
    ankerl::nanobench::Bench().run("rttr find method cross cast neg level 3", [&]() {
        if ((m = rttr::type::get(obj_base).get_method("method_15"))) //method 15 is contained in 'class_multiple_3C'
        {
            value = 1;
        }
        ankerl::nanobench::doNotOptimizeAway(static_cast<std::size_t>(value));
    });
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void bench_native_find_method_cross_cast_neg_level_6()
{
    ns_foo::class_multiple_final obj_final;
    ns_foo::class_multiple_base_C& obj_base = obj_final;
    volatile std::size_t value = 0;
    
    ankerl::nanobench::Bench().run("native find method cross cast neg level 6", [&]() {
        if (dynamic_cast<ns_foo::class_multiple_final_D*>(&obj_base))
        {
            value = 1;
        }
        ankerl::nanobench::doNotOptimizeAway(static_cast<std::size_t>(value));
    });
}

/////////////////////////////////////////////////////////////////////////////////////////

void bench_rttr_find_method_cross_cast_neg_level_6()
{
    ns_foo::class_multiple_final obj_final;
    ns_foo::class_multiple_base_C& obj_base = obj_final;
    volatile std::size_t value = 0;
    rttr::method m = rttr::type::get(nullptr).get_method("");
    
    ankerl::nanobench::Bench().run("rttr find method cross cast neg level 6", [&]() {
        if ((m = rttr::type::get(obj_base).get_method("method_19"))) //method 19 is contained in 'class_multiple_final_D'
        {
            value = 1;
        }
        ankerl::nanobench::doNotOptimizeAway(static_cast<std::size_t>(value));
    });
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void bench_find_method()
{
    std::cout << "Single hierarchy - Level 1:" << std::endl;
    bench_native_find_method_level_1();
    bench_rttr_find_method_level_1();

    std::cout << "Single hierarchy - Level 3:" << std::endl;
    bench_native_find_method_level_3();
    bench_rttr_find_method_level_3();

    std::cout << "Single hierarchy - Level 6:" << std::endl;
    bench_native_find_method_level_6();
    bench_rttr_find_method_level_6();

    std::cout << "Across hierarchy - Level 1:" << std::endl;
    bench_native_find_method_cross_cast_level_1();
    bench_rttr_find_method_cross_cast_level_1();

    std::cout << "Across hierarchy - Level 3:" << std::endl;
    bench_native_find_method_cross_cast_level_3();
    bench_rttr_find_method_cross_cast_level_3();

    std::cout << "Across hierarchy - Level 6:" << std::endl;
    bench_native_find_method_cross_cast_level_6();
    bench_rttr_find_method_cross_cast_level_6();

    std::cout << "Negative single hierarchy - Level 1:" << std::endl;
    bench_native_find_method_neg_level_1();
    bench_rttr_find_method_neg_level_1();

    std::cout << "Negative single hierarchy - Level 3:" << std::endl;
    bench_native_find_method_neg_level_3();
    bench_rttr_find_method_neg_level_3();

    std::cout << "Negative single hierarchy - Level 6:" << std::endl;
    bench_native_find_method_neg_level_6();
    bench_rttr_find_method_neg_level_6();

    std::cout << "Negative across hierarchy - Level 1:" << std::endl;
    bench_native_find_method_cross_cast_neg_level_1();
    bench_rttr_find_method_cross_cast_neg_level_1();

    std::cout << "Negative across hierarchy - Level 3:" << std::endl;
    bench_native_find_method_cross_cast_neg_level_3();
    bench_rttr_find_method_cross_cast_neg_level_3();

    std::cout << "Negative across hierarchy - Level 6:" << std::endl;
    bench_native_find_method_cross_cast_neg_level_6();
    bench_rttr_find_method_cross_cast_neg_level_6();
}
