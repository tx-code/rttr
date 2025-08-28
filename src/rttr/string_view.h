
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

#ifndef RTTR_STRING_VIEW_H_
#define RTTR_STRING_VIEW_H_

#include "rttr/detail/base/core_prerequisites.h"

#include <string>
#include <ostream>

namespace rttr
{

/*!
 * The class template \ref basic_string_view describes an non-owning reference to a
 * constant contiguous sequence of char-like objects.
 *
 * The purpose of this class is to avoid copying of data which is already owned somewhere else.
 * Creating a basic_string_view will never do any heap allocation.
 */
template<typename CharT, typename Traits = std::char_traits<CharT> >
class basic_string_view
{
    public:
        using traits_type       = Traits;
        using value_type        = CharT;
        using pointer           = CharT*;
        using const_pointer     = const CharT*;
        using reference         = CharT&;
        using const_reference   = const CharT&;
        using const_iterator    = const_pointer;
        using iterator          = const_iterator;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;
        using reverse_iterator  = const_reverse_iterator;
        using size_type         = std::size_t;
        using difference_type   = std::ptrdiff_t;
        static constexpr size_type npos = size_type(-1);

        /*!
         * \brief Default constructor. Constructs an empty basic_string_view.
         */
        constexpr basic_string_view() noexcept;

        /*!
         * \brief Copy constructor. Constructs a view of the same content as \p other.
         */
        constexpr basic_string_view(const basic_string_view& other) noexcept;

        /*!
         * \brief Constructs a view of the null-terminated character string pointed to by \p str, not including the terminating null character.
         *        The length of the view is determined as if by `Traits::length(str)`.
         *        The behavior is undefined if `[str, str + Traits::length(str))` is not a valid range
         *        (even though the constructor may not access any of the elements of this range).
         */
        constexpr basic_string_view(const CharT* str);

        /*!
         * \brief Constructs a view of the first count characters of the character array starting with the element pointed by \p str.
         *        \p str can contain null characters.
         *        The behavior is undefined if `[str, str + count)` is not a valid range
         *        (even though the constructor may not access any of the elements of this range).
         */
        constexpr basic_string_view(const CharT* str, size_type len);

        /*!
         * \brief Constructs a view of the first \p str.size() characters of the character array
         *        starting with the element pointed by \p str.data().
         */
        template<typename Allocator>
        basic_string_view(const std::basic_string<CharT, Traits, Allocator>& str) noexcept;

        /*!
         * \brief Replaces the this view with that of \p other view.
         */
        basic_string_view& operator=(const basic_string_view& other) noexcept;
        constexpr void swap(basic_string_view& s) noexcept;

        /*!
         * \brief Returns an iterator to the beginning of the view.
         *
         * \return const_iterator to the first character of this view.
         */
        constexpr const_iterator begin() const noexcept;

        /*!
         * \brief Returns an iterator to the beginning of the view.
         *
         * \return const_iterator to the first character of this view.
         */
        constexpr const_iterator cbegin() const noexcept;

        /*!
         * \brief Returns an iterator to the character following the last character of the view.
         *        Do **not** access this character, it will result in undefined behavior.
         *
         * \return const_iterator to the character following the last character.
         */
        constexpr const_iterator end() const noexcept;

        /*!
         * \brief Returns an iterator to the character following the last character of the view.
         *        Do **not** access this character, it will result in undefined behavior.
         *
         * \return const_iterator to the character following the last character.
         */
        constexpr const_iterator cend() const noexcept;

        /*!
         * \brief Returns a reverse iterator to the first character of the reversed view.
         *        It corresponds to the last character of the non-reversed view.
         *
         * \return const_reverse_iterator to the first character.
         */
        const_reverse_iterator rbegin() const noexcept;

        /*!
         * \brief Returns a reverse iterator to the first character of the reversed view.
         *        It corresponds to the last character of the non-reversed view.
         *
         * \return const_reverse_iterator to the first character.
         */
        const_reverse_iterator crbegin() const noexcept;

        /*!
         * \brief Returns a reverse iterator to the character following the last character of the reversed view.
         *        It corresponds to the character preceding the first character of the non-reversed view.
         *        Do **not** access this character, it will result in undefined behavior.
         *
         * \return const_reverse_iterator to the character following the last character.
         */
        const_reverse_iterator rend() const noexcept;

        /*!
         * \brief Returns a reverse iterator to the character following the last character of the reversed view.
         *        It corresponds to the character preceding the first character of the non-reversed view.
         *        Do **not** access this character, it will result in undefined behavior.
         *
         * \return const_reverse_iterator to the character following the last character.
         */
        const_reverse_iterator crend() const noexcept;

        /*!
         * \brief Returns the number of `CharT` elements in the view, i.e. `std::distance(begin(), end())`.
         *
         * \return The number of `CharT` elements in the view.
         */
        constexpr size_type size() const noexcept;

        /*!
         * \brief Returns the number of `CharT` elements in the view, i.e. `std::distance(begin(), end())`.
         *
         * \return The number of `CharT` elements in the view.
         */
        constexpr size_type length() const noexcept;

        /*!
         * \brief The largest possible number of char-like objects that can be referred to by a \ref basic_string_view.
         *
         * \return Maximum number of characters.
         */
        constexpr size_type max_size() const noexcept;

        /*!
         * \brief Checks if the view has no characters, i.e. whether size() == 0.
         *
         * \return `true` if the view is empty, `false` otherwise.
         */
        constexpr bool empty() const noexcept;

        /*!
         * \brief Returns a const reference to the character at specified location \p pos.
         *        No bounds checking is performed: the behavior is undefined if `pos >= size()`.
         *
         * \return Const reference to the requested character.
         */
        constexpr const_reference operator[](size_type pos) const noexcept;

        /*!
         * \brief Returns reference to the first character in the view.
         *
         * \return Reference to the first character, equivalent to `operator[](0)`.
         */
        constexpr const_reference front() const;

        /*!
         * \brief Returns reference to the last character in the view.
         *
         * \return Reference to the last character, equivalent to `operator[](size() - 1)`.
         */
        constexpr const_reference back() const;

        /*!
         * \brief Returns a pointer to the underlying character array.
         *        The pointer is such that the range `[data(); data() + size())` is valid and the values in it correspond to the values of the view.
         *
         * \remark Passing \ref data() to a function which takes a `const CharT*` may not work,
         *         because the underlying buffer may **not** contain a null-terminated character.
         *
         * \return A pointer to the underlying character array.
         */
        constexpr const_pointer data() const noexcept;

        /*!
         * \brief Moves the start of the view forward by n characters.
         *        The behavior is undefined if `n > size()`.
         */
        constexpr void remove_prefix(size_type n) noexcept;

        /*!
         * \brief Moves the end of the view back by n characters.
         *        The behavior is undefined if `n > size()`.
         */
        constexpr void remove_suffix(size_type n) noexcept;


        /*!
         * \brief Creates a `basic_string` with a copy of the content of the current view.
         *
         * \return A basic_string containing a copy of the characters of the current view.
         */
        template<typename Allocator>
        explicit operator std::basic_string<CharT, Traits, Allocator>() const;

        /*!
         * \brief Creates a `basic_string` with a copy of the content of the current view.
         *
         * \return A `basic_string` containing a copy of the characters of the current view.
         */
        template<typename Allocator = std::allocator<CharT> >
        std::basic_string<CharT, Traits> to_string(const Allocator& a = Allocator()) const;

        /*!
         * \brief The function compares the two views by calling `Traits::compare(data(), v.data(), length)`,
         *        where \p length is the small of `size()` and `v.size()`.
         *
         * \return negative value if this view is less than the other character sequence,
         *         zero if the both character sequences are equal,
         *         positive value if this view is greater than the other character sequence.
         */
        constexpr int compare(basic_string_view v) const noexcept;

        /*!
         * \brief Equivalent to `compare(basic_string_view(c))`.
         *
         * \return negative value if this view is less than the other character sequence,
         *         zero if the both character sequences are equal,
         *         positive value if this view is greater than the other character sequence.
         */
        constexpr int compare(const CharT* c) const noexcept;

    private:
        const value_type*   m_data;
        size_type           m_size;
};

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
// friend functions
// MSVC 2013 cannot handle type deduction correctly, thats why we have to declare and
// define all possibility compares explicitly

/*!
 * \brief Compares the two views \p lhs and \p rhs.
 *        Two views are equal if both the \ref size() of \p lhs and \p rhs are equal
 *        and each character in \p lhs has an equivalent character in \p rhs at the same position.
 *
 * \return `true` when both views are the same, otherwise `false`.
 */
template<typename CharT, typename Traits>
inline constexpr bool operator==(basic_string_view<CharT, Traits> lhs,
                                                 basic_string_view<CharT, Traits> rhs) noexcept;

template<typename CharT, typename Traits>
inline constexpr bool operator==(const char* lhs,
                                                 basic_string_view<CharT, Traits> rhs) noexcept;

template<typename CharT, typename Traits>
inline constexpr bool operator==(basic_string_view<CharT, Traits> lhs,
                                                 const char* rhs) noexcept;

template<typename CharT, typename Traits>
inline constexpr bool operator==(const std::basic_string<CharT, Traits>& lhs,
                                                 basic_string_view<CharT, Traits> rhs) noexcept;

template<typename CharT, typename Traits>
inline constexpr bool operator==(basic_string_view<CharT, Traits> lhs,
                                                 const std::basic_string<CharT, Traits>& rhs) noexcept;

/////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Compares the two views \p lhs and \p rhs.
 *        Two views are not equal if the \ref size() differ or
 *        the characters of \p lhs are not equivalent and in the same position in \p rhs.
  *
 * \return `true` when both views are **not** the same, otherwise `false`.
 */
template<typename CharT, typename Traits>
inline constexpr bool operator!=(basic_string_view<CharT, Traits> lhs,
                                                 basic_string_view<CharT, Traits> rhs) noexcept;

template<typename CharT, typename Traits>
inline constexpr bool operator!=(const char* lhs,
                                                 basic_string_view<CharT, Traits> rhs) noexcept;

template<typename CharT, typename Traits>
inline constexpr bool operator!=(basic_string_view<CharT, Traits> lhs,
                                                 const char* rhs) noexcept;

template<typename CharT, typename Traits>
inline constexpr bool operator!=(const std::basic_string<CharT, Traits>& lhs,
                                                 basic_string_view<CharT, Traits> rhs) noexcept;

template<typename CharT, typename Traits>
inline constexpr bool operator!=(basic_string_view<CharT, Traits> lhs,
                                                 const std::basic_string<CharT, Traits>& rhs) noexcept;

/////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Compares the two views \p lhs and \p rhs.
 *        The ordering comparisons is done lexicographically.
 *        The comparison is performed by a function equivalent to `std::lexicographical_compare`.
  *
 * \return `true` when lhs is smaller or equal to \p rhs, otherwise false.
 */
template<typename CharT, typename Traits>
inline constexpr bool operator<=(basic_string_view<CharT, Traits> lhs,
                                                 basic_string_view<CharT, Traits> rhs) noexcept;

template<typename CharT, typename Traits>
inline constexpr bool operator<=(const char* lhs,
                                                 basic_string_view<CharT, Traits> rhs) noexcept;

template<typename CharT, typename Traits>
inline constexpr bool operator<=(basic_string_view<CharT, Traits> lhs,
                                                 const char* rhs) noexcept;

template<typename CharT, typename Traits>
inline constexpr bool operator<=(const std::basic_string<CharT, Traits>& lhs,
                                                 basic_string_view<CharT, Traits> rhs) noexcept;

template<typename CharT, typename Traits>
inline constexpr bool operator<=(basic_string_view<CharT, Traits> lhs,
                                                 const std::basic_string<CharT, Traits>& rhs) noexcept;

/////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Compares the two views \p lhs and \p rhs.
 *        The ordering comparisons is done lexicographically.
 *        The comparison is performed by a function equivalent to `std::lexicographical_compare`.
  *
 * \return `true` when lhs is greater or equal to \p rhs, otherwise false.
 */
template<typename CharT, typename Traits>
inline constexpr bool operator>=(basic_string_view<CharT, Traits> lhs,
                                                 basic_string_view<CharT, Traits> rhs) noexcept;

template<typename CharT, typename Traits>
inline constexpr bool operator>=(const char* lhs,
                                                 basic_string_view<CharT, Traits> rhs) noexcept;

template<typename CharT, typename Traits>
inline constexpr bool operator>=(basic_string_view<CharT, Traits> lhs,
                                                 const char* rhs) noexcept;

template<typename CharT, typename Traits>
inline constexpr bool operator>=(const std::basic_string<CharT, Traits>& lhs,
                                                 basic_string_view<CharT, Traits> rhs) noexcept;

template<typename CharT, typename Traits>
inline constexpr bool operator>=(basic_string_view<CharT, Traits> lhs,
                                                 const std::basic_string<CharT, Traits>& rhs) noexcept;

/////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Compares the two views \p lhs and \p rhs.
 *        The ordering comparisons is done lexicographically.
 *        The comparison is performed by a function equivalent to `std::lexicographical_compare`.
  *
 * \return `true` when lhs is greater than \p rhs, otherwise false.
 */
template<typename CharT, typename Traits>
inline constexpr bool operator>(basic_string_view<CharT, Traits> lhs,
                                                basic_string_view<CharT, Traits> rhs) noexcept;

template<typename CharT, typename Traits>
inline constexpr bool operator>(const char* lhs,
                                                basic_string_view<CharT, Traits> rhs) noexcept;

template<typename CharT, typename Traits>
inline constexpr bool operator>(basic_string_view<CharT, Traits> lhs,
                                                const char* rhs) noexcept;

template<typename CharT, typename Traits>
inline constexpr bool operator>(const std::basic_string<CharT, Traits>& lhs,
                                                basic_string_view<CharT, Traits> rhs) noexcept;

template<typename CharT, typename Traits>
inline constexpr bool operator>(basic_string_view<CharT, Traits> lhs,
                                                const std::basic_string<CharT, Traits>& rhs) noexcept;

/////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Compares the two views \p lhs and \p rhs.
 *        The ordering comparisons is done lexicographically.
 *        The comparison is performed by a function equivalent to `std::lexicographical_compare`.
  *
 * \return `true` when lhs is smaller than \p rhs, otherwise false.
 */
template<typename CharT, typename Traits>
inline constexpr bool operator<(basic_string_view<CharT, Traits> lhs,
                                                basic_string_view<CharT, Traits> rhs) noexcept;

template<typename CharT, typename Traits>
inline constexpr bool operator<(const char* lhs,
                                                basic_string_view<CharT, Traits> rhs) noexcept;

template<typename CharT, typename Traits>
inline constexpr bool operator<(basic_string_view<CharT, Traits> lhs,
                                                const char* rhs) noexcept;

template<typename CharT, typename Traits>
inline constexpr bool operator<(const std::basic_string<CharT, Traits>& lhs,
                                                basic_string_view<CharT, Traits> rhs) noexcept;

template<typename CharT, typename Traits>
inline constexpr bool operator<(basic_string_view<CharT, Traits> lhs,
                                                const std::basic_string<CharT, Traits>& rhs) noexcept;

/////////////////////////////////////////////////////////////////////////////////////////

template<typename CharT, typename Traits>
inline std::basic_string<CharT, Traits> operator+(basic_string_view<CharT, Traits> lhs,
                                                       const std::basic_string<CharT, Traits>& rhs);

template<typename CharT, typename Traits>
inline std::basic_string<CharT, Traits> operator+(const std::basic_string<CharT, Traits>& lhs,
                                                       basic_string_view<CharT, Traits> rhs);

template<typename CharT, typename Traits>
inline std::basic_string<CharT, Traits> operator+(basic_string_view<CharT, Traits> lhs,
                                                       std::basic_string<CharT, Traits>&& rhs);

template<typename CharT, typename Traits>
inline std::basic_string<CharT, Traits> operator+(std::basic_string<CharT, Traits>&& lhs,
                                                       basic_string_view<CharT, Traits> rhs);

/////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Performs a stream output on a basic_string_view .
 *
 * \return os
 */
template <typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os,
                                              basic_string_view<CharT, Traits> v);

/*!
 * A class to hold a reference to a continuous sequence of `char` objects.
 */
using string_view = basic_string_view<char>;


} // end namespace rttr

#include "rttr/detail/impl/string_view_impl.h"

#endif // RTTR_STRING_VIEW_H_
