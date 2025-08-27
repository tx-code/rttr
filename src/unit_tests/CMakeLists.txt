####################################################################################
#                                                                                  #
#  Copyright (c) 2014 - 2018 Axel Menzel <info@rttr.org>                           #
#                                                                                  #
#  This file is part of RTTR (Run Time Type Reflection)                            #
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

add_subdirectory(base_library)

set(HPP_FILES "")
set(SRC_FILES "")

project(unit_tests LANGUAGES CXX)

message(STATUS "Scanning "  ${PROJECT_NAME} " module.")
message(STATUS "===========================")

generateLibraryVersionVariables(${RTTR_VERSION_MAJOR} ${RTTR_VERSION_MINOR} ${RTTR_VERSION_PATCH}
                                "RTTR unit_tests" "Copyright (c) 2014 - 2018 Axel Menzel <info@rttr.org>" "MIT License")

loadFolder("unit_tests" HPP_FILES SRC_FILES)

if (USE_PCH)
  activate_precompiled_headers("pch.h" SRC_FILES)
endif()

find_package(Catch2 CONFIG REQUIRED)

add_executable(unit_tests ${SRC_FILES} ${HPP_FILES})
target_link_libraries(unit_tests RTTR::Core unit_test_base Catch2::Catch2WithMain)
add_dependencies(unit_tests RTTR::Core)
set_target_properties(unit_tests PROPERTIES DEBUG_POSTFIX ${RTTR_DEBUG_POSTFIX}
                                            FOLDER "Testing"
                                            INSTALL_RPATH "${RTTR_EXECUTABLE_INSTALL_RPATH}"
                                            CXX_STANDARD ${MAX_CXX_STANDARD})

set_compiler_warnings(unit_tests)

if (MSVC)
    target_compile_options(unit_tests PRIVATE /bigobj)
endif()

# Configure CTest integration
if (CMAKE_PROJECT_NAME STREQUAL "rttr" AND BUILD_UNIT_TESTS)
    # Enable testing and include Catch2 test discovery
    enable_testing()
    include(Catch)
    
    # Set test properties for better execution
    set(RTTR_TEST_PROPERTIES
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        ENVIRONMENT "PATH=$<TARGET_FILE_DIR:unit_tests>;$ENV{PATH}"
    )
    
    # Windows DLL handling
    if(WIN32)
        list(APPEND RTTR_TEST_PROPERTIES
            ENVIRONMENT "PATH=$<TARGET_FILE_DIR:unit_test_base>;$<TARGET_FILE_DIR:RTTR::Core>;$ENV{PATH}")
    endif()
    
    # Create test results directory
    file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/test_results")
    
    # Discover Catch2 tests automatically
    catch_discover_tests(unit_tests
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        PROPERTIES ${RTTR_TEST_PROPERTIES}
    )
    
    message(STATUS "CTest integration enabled for unit_tests")
endif()


add_subdirectory(plugin)

add_dependencies(unit_tests unit_test_plugin)

message(STATUS "Scanning " ${PROJECT_NAME} " module finished!")
message(STATUS "")