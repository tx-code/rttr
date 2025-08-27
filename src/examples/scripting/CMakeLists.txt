####################################################################################
#                                                                                  #
#  Copyright (c) 2014 - 2018 Axel Menzel <info@rttr.org>                           #
#                                                                                  #
#  This file is part of the examples of RTTR (Run Time Type Reflection)            #
#  License: MIT License                                                            #
#                                                                                  #
#  Permission is hereby granted, free of charge, to any person obtaining           #
#  a copy of this software and associated documentation files (the "Software"),    #
#  to deal in the Software without restriction, including without limitation       #
#  the rights to use, copy, modify, merge, publish, distribute, sublicense,        #
#  and/or sell copies of the Software, and to permit persons to whom the           #
#  Software is furnished to do so, subject to the following conditions:            #
#                                                                                  #
#  The above copyright notice and this permission notice shall be included in      #
#  all copies or substantial portions of the Software.                             #
#                                                                                  #
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR      #
#  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,        #
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE     #
#  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER          #
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,   #
#  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE   #
#  SOFTWARE.                                                                       #
#                                                                                  #
####################################################################################

project(scripting_example LANGUAGES CXX)

# Find required packages
find_package(Threads REQUIRED)

generateLibraryVersionVariables(${RTTR_VERSION_MAJOR} ${RTTR_VERSION_MINOR} ${RTTR_VERSION_PATCH}
                                "RTTR Examples: scripting binding" "Copyright (c) 2014 - 2018 Axel Menzel <info@rttr.org>" "MIT License")

loadFolder("files" HPP_FILES SRC_FILES)

if (USE_PCH)
  activate_precompiled_headers("pch.h" SRC_FILES)
endif()

add_executable(scripting_example ${SRC_FILES} ${HPP_FILES})
target_link_libraries(scripting_example RTTR::Core ChaiScript::ChaiScript ${CMAKE_DL_LIBS} Threads::Threads)

# C++20 compatibility fixes for ChaiScript
target_compile_definitions(scripting_example PRIVATE 
    _SILENCE_CXX20_IS_POD_DEPRECATION_WARNING
    _SILENCE_ALL_CXX20_DEPRECATION_WARNINGS)

# Suppress ChaiScript-specific warnings
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(scripting_example PRIVATE 
        -Wno-defaulted-function-deleted
    )
elseif(MSVC)
    target_compile_options(scripting_example PRIVATE 
        /wd4624  # destructor was implicitly defined as deleted
        /wd4625  # copy constructor was implicitly defined as deleted  
        /wd4626  # assignment operator was implicitly defined as deleted
        /wd5267  # implicit copy constructor is deprecated
    )
endif()

set_target_properties(scripting_example 
                       PROPERTIES DEBUG_POSTFIX ${RTTR_DEBUG_POSTFIX}
                                  FOLDER "Examples"
                                  INSTALL_RPATH "${RTTR_EXECUTABLE_INSTALL_RPATH}"
                                  CXX_STANDARD 17)

# Force C++17 for ChaiScript compatibility
target_compile_options(scripting_example PRIVATE 
    $<$<CXX_COMPILER_ID:Clang>:-std=c++17>
    $<$<CXX_COMPILER_ID:MSVC>:/std:c++17>
    $<$<CXX_COMPILER_ID:GNU>:-std=c++17>)
if (MSVC)
    target_compile_options(scripting_example PRIVATE /bigobj) 
endif()

add_dependencies(examples scripting_example)

