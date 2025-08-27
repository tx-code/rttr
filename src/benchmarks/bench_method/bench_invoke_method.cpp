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

void bench_native_invoke_method_void_return_value()
{
    ns_foo::method_class obj;
    ankerl::nanobench::Bench().run("native method invoke (void return)", [&]() {
        obj.method_0();
        ankerl::nanobench::doNotOptimizeAway(obj);
    });
}

/////////////////////////////////////////////////////////////////////////////////////////

void bench_rttr_invoke_method_void_return_value()
{
    ns_foo::method_class obj;
    rttr::method m = rttr::type::get(obj).get_method("method_0");
    ankerl::nanobench::Bench().run("rttr method invoke (void return)", [&]() {
        auto result = m.invoke(obj);
        ankerl::nanobench::doNotOptimizeAway(result);
    });
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void bench_native_invoke_method_int_return_value()
{
    ns_foo::method_class obj;
    ankerl::nanobench::Bench().run("native method invoke (int return)", [&]() {
        auto result = obj.int_method();
        ankerl::nanobench::doNotOptimizeAway(result);
    });
}

/////////////////////////////////////////////////////////////////////////////////////////

void bench_rttr_invoke_method_int_return_value()
{
    ns_foo::method_class obj;
    rttr::method m = rttr::type::get(obj).get_method("int_method");
    ankerl::nanobench::Bench().run("rttr method invoke (int return)", [&]() {
        auto result = m.invoke(obj);
        ankerl::nanobench::doNotOptimizeAway(result);
    });
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void bench_native_invoke_method_string_return_value()
{
    ns_foo::method_class obj;
    ankerl::nanobench::Bench().run("native method invoke (string return)", [&]() {
        auto result = obj.string_method();
        ankerl::nanobench::doNotOptimizeAway(result);
    });
}

/////////////////////////////////////////////////////////////////////////////////////////

void bench_rttr_invoke_method_string_return_value()
{
    ns_foo::method_class obj;
    rttr::method m = rttr::type::get(obj).get_method("string_method");
    ankerl::nanobench::Bench().run("rttr method invoke (string return)", [&]() {
        auto result = m.invoke(obj);
        ankerl::nanobench::doNotOptimizeAway(result);
    });
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void bench_native_invoke_method_arg_1()
{
    ns_foo::method_class obj;
    ankerl::nanobench::Bench().run("native method invoke (1 arg)", [&]() {
        obj.void_method_arg_1(23);
        ankerl::nanobench::doNotOptimizeAway(obj);
    });
}

/////////////////////////////////////////////////////////////////////////////////////////

void bench_rttr_invoke_method_arg_1()
{
    ns_foo::method_class obj;
    rttr::method m = rttr::type::get(obj).get_method("void_method_arg_1");
    ankerl::nanobench::Bench().run("rttr method invoke (1 arg)", [&]() {
        auto result = m.invoke(obj, 23);
        ankerl::nanobench::doNotOptimizeAway(result);
    });
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void bench_native_invoke_method_arg_2()
{
    ns_foo::method_class obj;
    ankerl::nanobench::Bench().run("native method invoke (2 args)", [&]() {
        obj.void_method_arg_2(23, 42);
        ankerl::nanobench::doNotOptimizeAway(obj);
    });
}

/////////////////////////////////////////////////////////////////////////////////////////

void bench_rttr_invoke_method_arg_2()
{
    ns_foo::method_class obj;
    rttr::method m = rttr::type::get(obj).get_method("void_method_arg_2");
    ankerl::nanobench::Bench().run("rttr method invoke (2 args)", [&]() {
        auto result = m.invoke(obj, 23, 42);
        ankerl::nanobench::doNotOptimizeAway(result);
    });
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void bench_native_invoke_method_arg_3()
{
    ns_foo::method_class obj;
    ankerl::nanobench::Bench().run("native method invoke (3 args)", [&]() {
        obj.void_method_arg_3(23, 42, 5);
        ankerl::nanobench::doNotOptimizeAway(obj);
    });
}

/////////////////////////////////////////////////////////////////////////////////////////

void bench_rttr_invoke_method_arg_3()
{
    ns_foo::method_class obj;
    rttr::method m = rttr::type::get(obj).get_method("void_method_arg_3");
    ankerl::nanobench::Bench().run("rttr method invoke (3 args)", [&]() {
        auto result = m.invoke(obj, 23, 42, 5);
        ankerl::nanobench::doNotOptimizeAway(result);
    });
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void bench_native_invoke_method_arg_8()
{
    ns_foo::method_class obj;
    ankerl::nanobench::Bench().run("native method invoke (8 args)", [&]() {
        obj.void_method_arg_8(1, 2, 3, 4, 5, 6, 7, 8);
        ankerl::nanobench::doNotOptimizeAway(obj);
    });
}

/////////////////////////////////////////////////////////////////////////////////////////

void bench_rttr_invoke_method_arg_8()
{
    ns_foo::method_class obj;
    rttr::method m = rttr::type::get(obj).get_method("void_method_arg_8");
    std::vector<rttr::argument> args = {1, 2, 3, 4, 5, 6, 7, 8};
    ankerl::nanobench::Bench().run("rttr method invoke (8 args)", [&]() {
        auto result = m.invoke_variadic(obj, args);
        ankerl::nanobench::doNotOptimizeAway(result);
    });
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void bench_native_invoke_method_ptr_arg()
{
    ns_foo::method_class obj;
    int* ptr = nullptr;
    ankerl::nanobench::Bench().run("native method invoke (ptr arg)", [&]() {
        obj.method_ptr_arg(ptr);
        ankerl::nanobench::doNotOptimizeAway(obj);
    });
}

/////////////////////////////////////////////////////////////////////////////////////////

void bench_rttr_invoke_method_ptr_arg()
{
    ns_foo::method_class obj;
    rttr::method m = rttr::type::get(obj).get_method("method_ptr_arg");
    int* ptr = nullptr;
    ankerl::nanobench::Bench().run("rttr method invoke (ptr arg)", [&]() {
        auto result = m.invoke(obj, ptr);
        ankerl::nanobench::doNotOptimizeAway(result);
    });
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void bench_invoke_method()
{
    std::cout << "=== Method Invocation Benchmark ==="<< std::endl;
    std::cout << "Running benchmarks for RTTR method invocation vs native method calls..." << std::endl << std::endl;

    std::cout << "[Group: void return value]" << std::endl;
    bench_native_invoke_method_void_return_value();
    bench_rttr_invoke_method_void_return_value();
    std::cout << std::endl;

    std::cout << "[Group: int return value]" << std::endl;
    bench_native_invoke_method_int_return_value();
    bench_rttr_invoke_method_int_return_value();
    std::cout << std::endl;

    std::cout << "[Group: string return value]" << std::endl;
    bench_native_invoke_method_string_return_value();
    bench_rttr_invoke_method_string_return_value();
    std::cout << std::endl;

    std::cout << "[Group: 1 argument]" << std::endl;
    bench_native_invoke_method_arg_1();
    bench_rttr_invoke_method_arg_1();
    std::cout << std::endl;

    std::cout << "[Group: 2 arguments]" << std::endl;
    bench_native_invoke_method_arg_2();
    bench_rttr_invoke_method_arg_2();
    std::cout << std::endl;

    std::cout << "[Group: 3 arguments]" << std::endl;
    bench_native_invoke_method_arg_3();
    bench_rttr_invoke_method_arg_3();
    std::cout << std::endl;

    std::cout << "[Group: 8 arguments (variadic)]" << std::endl;
    bench_native_invoke_method_arg_8();
    bench_rttr_invoke_method_arg_8();
    std::cout << std::endl;

    std::cout << "[Group: pointer argument]" << std::endl;
    bench_native_invoke_method_ptr_arg();
    bench_rttr_invoke_method_ptr_arg();
    std::cout << std::endl;

    std::cout << "=== Benchmark Complete ===" << std::endl;
}
