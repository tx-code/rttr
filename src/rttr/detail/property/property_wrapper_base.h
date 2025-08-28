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

#ifndef RTTR_PROPERTY_WRAPPER_BASE_H_
#define RTTR_PROPERTY_WRAPPER_BASE_H_

#include "rttr/detail/base/core_prerequisites.h"
#include "rttr/detail/metadata/metadata_handler.h"
#include "rttr/type.h"
#include "rttr/variant.h"
#include "rttr/access_levels.h"
#include "rttr/string_view.h"

namespace rttr
{

class instance;
class argument;
class visitor;

namespace detail
{
/*!
 * Base class for an instance of a Property.
 *
 * This is the base class for all properties of the system.
 * It provide the basic mechanism for getting all meta data of a property,
 * but it also define a general interface to set/get properties via string: toString and fromString.
 */
class RTTR_API property_wrapper_base
{
    public:
        property_wrapper_base(string_view name, type declaring_type) noexcept;

        virtual ~property_wrapper_base();

        type get_declaring_type() const noexcept;

        string_view get_name() const noexcept;

        virtual bool is_valid() const noexcept;

        virtual access_levels get_access_level() const noexcept;

        virtual bool is_readonly() const noexcept;

        virtual bool is_static() const noexcept;

        virtual type get_type() const noexcept;

        virtual variant get_metadata(const variant& key) const;

        virtual bool set_value(instance& object, argument& arg) const;

        virtual variant get_value(instance& object) const;

        virtual void visit(visitor& visitor, property prop) const noexcept;

    protected:
        void init() noexcept;

    private:
        string_view m_name;
        type        m_declaring_type;
};

} // end namespace detail
} // end namespace rttr

#endif // RTTR_PROPERTY_WRAPPER_BASE_H_
