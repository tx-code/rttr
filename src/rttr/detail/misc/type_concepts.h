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

#ifndef RTTR_TYPE_CONCEPTS_H_
#define RTTR_TYPE_CONCEPTS_H_

#include "rttr/detail/base/core_prerequisites.h"
#include "rttr/detail/misc/function_traits.h"
#include "rttr/detail/misc/std_type_traits.h"

#include <type_traits>
#include <concepts>

// Forward declarations
namespace rttr {
    class type;
}

namespace rttr::detail {

// Forward declarations for RTTR-specific types
struct derived_info;
struct invalid_type;

// C++20 Concepts for type traits modernization

// Basic type concepts
template<typename T>
concept PointerType = std::is_pointer_v<T>;

template<typename T>
concept ReferenceType = std::is_reference_v<T>;

template<typename T>
concept ArrayType = std::is_array_v<T>;

template<typename T>
concept FunctionPointer = is_function_ptr<T>::value;

template<typename T>
concept PointerButNotFunction = PointerType<T> && !FunctionPointer<T>;

template<typename T>
concept PointerButNotMemberPointer = PointerType<T> && !std::is_member_pointer_v<T>;

template<typename T>
concept ValidPointerForCount = PointerType<T> && !FunctionPointer<T> && !std::is_member_pointer_v<T>;

// Container concepts
template<typename T>
concept HasMappedType = requires {
    typename T::mapped_type;
};

template<typename T>
concept HasIsValidAlias = requires {
    typename T::is_valid;
};

// Member function detection concepts - using SFINAE-compatible approach for complex cases
template<typename T>
struct has_get_type_method_helper {
    template<typename U>
    static auto test(int) -> decltype(std::declval<const U>().get_type(), std::true_type{});
    template<typename>
    static std::false_type test(...);
    using type = decltype(test<T>(0));
};

template<typename T>
concept HasGetTypeMethod = has_get_type_method_helper<T>::type::value;

template<typename T>
struct has_get_ptr_method_helper {
    template<typename U>
    static auto test(int) -> decltype(std::declval<U>().get_ptr(), std::true_type{});
    template<typename>
    static std::false_type test(...);
    using type = decltype(test<T>(0));
};

template<typename T>
concept HasGetPtrMethod = has_get_ptr_method_helper<T>::type::value;

template<typename T>
struct has_get_derived_info_method_helper {
    template<typename U>
    static auto test(int) -> decltype(std::declval<U>().get_derived_info(), std::true_type{});
    template<typename>
    static std::false_type test(...);
    using type = decltype(test<T>(0));
};

template<typename T>
concept HasGetDerivedInfoMethod = has_get_derived_info_method_helper<T>::type::value;

// Comparison operator concepts
template<typename T>
concept HasLessThanOperator = requires(const T& a, const T& b) {
    { a < b } -> std::convertible_to<bool>;
};

template<typename T>
concept HasEqualOperator = requires(const T& a, const T& b) {
    { a == b } -> std::convertible_to<bool>;
};

template<typename T>
concept HasThreeWayComparison = requires(const T& a, const T& b) {
    { a <=> b } -> std::convertible_to<std::strong_ordering>;
};

// String literal concept
template<typename T>
concept StringLiteral = std::same_as<T, const char*> || 
    (std::is_array_v<T> && std::same_as<std::remove_extent_t<T>, char>);

// Character array concept
template<typename T>
concept OneDimCharArray = std::is_array_v<T> && 
    std::same_as<char, std::remove_cv_t<std::remove_all_extents_t<T>>> &&
    (std::rank_v<T> == 1);

// Copy constructible concept (enhanced for RTTR types)
template<typename T>
concept CopyConstructibleRTTR = std::copy_constructible<T>;

// Type list concepts
template<typename... Ts>
concept EmptyTypeList = (sizeof...(Ts) == 0);

template<typename... Ts>
concept SingleTypeArgument = (sizeof...(Ts) == 1);

template<typename... Ts>
concept MultipleTypeArguments = (sizeof...(Ts) > 1);

// Template parameter pack concepts
template<template<class> class Condition, typename T>
concept SatisfiesCondition = Condition<T>::value;

// Nullptr comparison concept
template<typename T>
concept NullptrCompatible = std::is_pointer_v<T> || std::same_as<T, std::nullptr_t>;

// Container concepts for flat_map
template<typename T>
concept Hashable = requires(const T& t) {
    { std::hash<T>{}(t) } -> std::convertible_to<std::size_t>;
};

template<typename T>
concept EqualityComparable = requires(const T& a, const T& b) {
    { a == b } -> std::convertible_to<bool>;
};

template<typename Key>
concept FlatMapKey = Hashable<Key> && EqualityComparable<Key> && std::is_copy_constructible_v<Key>;

template<typename Value>
concept FlatMapValue = std::is_copy_constructible_v<Value> && std::is_assignable_v<Value&, const Value&>;

template<typename Hash, typename Key>
concept HashFunction = requires(const Hash& h, const Key& k) {
    { h(k) } -> std::convertible_to<std::size_t>;
};

template<typename Compare, typename Key>
concept CompareFunction = requires(const Compare& c, const Key& a, const Key& b) {
    { c(a, b) } -> std::convertible_to<bool>;
};

} // namespace rttr::detail

#endif // RTTR_TYPE_CONCEPTS_H_