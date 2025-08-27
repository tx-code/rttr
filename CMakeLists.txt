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

####################################################################################
# Modern CMake build system for RTTR (Run Time Type Reflection)
# Follows modern CMake best practices with target-based configuration
####################################################################################

# Require modern CMake version
cmake_minimum_required(VERSION 3.21)

# Project declaration with version and languages
project(rttr
    VERSION 0.9.7
    LANGUAGES CXX
    DESCRIPTION "C++ Run Time Type Reflection library"
    HOMEPAGE_URL "https://github.com/rttrorg/rttr"
)

# Only set policies when we're the main project
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    # Use modern CMake policies
    cmake_policy(SET CMP0077 NEW)  # option() honors normal variables
    cmake_policy(SET CMP0079 NEW)  # target_link_libraries() allows use with targets in other directories
    
    # Set policy for Boost module removal (CMake 3.30+)
    if(POLICY CMP0167)
        cmake_policy(SET CMP0167 NEW)  # The FindBoost module is removed
    endif()
    
    # Enable folder organization in IDEs
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
    
    # Enable testing support
    include(CTest)
    
    # Set default build type if not specified
    if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
        set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING
            "Choose the type of build: Debug Release RelWithDebInfo MinSizeRel" FORCE)
        set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
            "Debug" "Release" "RelWithDebInfo" "MinSizeRel")
    endif()
    
    # Use C++20 standard without compiler extensions
    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

# Add CMake module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")

####################################################################################
# Project Options (use modern option approach)
####################################################################################

# Core library options
option(RTTR_BUILD_SHARED "Build shared/dynamic library" ON)
option(RTTR_BUILD_STATIC "Build static library" OFF)
option(RTTR_BUILD_WITH_RTTI "Enable C++ RTTI support" ON)
option(RTTR_BUILD_WITH_STATIC_RUNTIME "Link against static runtime libraries" OFF)

# Feature options
option(RTTR_BUILD_TESTS "Build unit tests" ON)
option(RTTR_BUILD_EXAMPLES "Build examples" ON)
option(RTTR_BUILD_BENCHMARKS "Build benchmarks" ON)
option(RTTR_BUILD_DOCUMENTATION "Build documentation" ON)

# Development options
option(RTTR_USE_PCH "Use precompiled headers" ON)
option(RTTR_BUILD_INSTALLER "Build installer package" ON)
option(RTTR_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" OFF)

# Doxygen options
option(RTTR_CUSTOM_DOXYGEN_STYLE "Use custom doxygen style" ON)
option(RTTR_BUILD_WEBSITE_DOCS "Build documentation for website" OFF)

####################################################################################
# Validate options and set derived variables
####################################################################################

# Disable PCH for multiple target configurations (Ninja limitation)
if(RTTR_USE_PCH AND (RTTR_BUILD_STATIC OR RTTR_BUILD_WITH_STATIC_RUNTIME))
    message(STATUS "Disabling PCH due to multiple target build")
    set(RTTR_USE_PCH OFF)
endif()

# Ensure at least one library type is built
if(NOT RTTR_BUILD_SHARED AND NOT RTTR_BUILD_STATIC)
    message(STATUS "No library type specified, enabling shared library")
    set(RTTR_BUILD_SHARED ON)
endif()

####################################################################################
# Load configuration modules
####################################################################################

include(utility)        # Helper functions
include(config)         # Version and paths configuration
include(3rd_party_libs) # External dependencies

####################################################################################
# Global compiler settings (avoid directory-level commands when possible)
####################################################################################

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")

####################################################################################
# Add subdirectories
####################################################################################

# Core library
add_subdirectory(src)

# Optional components
if(RTTR_BUILD_DOCUMENTATION AND CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    add_subdirectory(doc)
endif()

####################################################################################
# Export and installation (only for main project)
####################################################################################

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND RTTR_BUILD_INSTALLER)
    include(installer)
    
    # Create and install CMake config files
    include(CMakePackageConfigHelpers)
    
    # Generate version file
    write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/rttr-config-version.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
    )
    
    # Generate config file
    configure_package_config_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/CMake/rttr-config.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/rttr-config.cmake"
        INSTALL_DESTINATION "${RTTR_CMAKE_CONFIG_INSTALL_DIR}"
    )
    
    # Install config files
    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/rttr-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/rttr-config-version.cmake"
        DESTINATION "${RTTR_CMAKE_CONFIG_INSTALL_DIR}"
        COMPONENT Development
    )
    
    # Export targets
    install(EXPORT rttr-targets
        FILE rttr-targets.cmake
        NAMESPACE RTTR::
        DESTINATION "${RTTR_CMAKE_CONFIG_INSTALL_DIR}"
        COMPONENT Development
    )
    
    # Install license and readme
    install(FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt"
        "${CMAKE_CURRENT_SOURCE_DIR}/README.md"
        DESTINATION "${RTTR_ADDITIONAL_FILES_INSTALL_DIR}"
        COMPONENT Documentation
    )
endif()

####################################################################################
# Summary
####################################################################################

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    message(STATUS "")
    message(STATUS "RTTR ${PROJECT_VERSION} Configuration Summary:")
    message(STATUS "  Build type:       ${CMAKE_BUILD_TYPE}")
    message(STATUS "  Shared library:   ${RTTR_BUILD_SHARED}")
    message(STATUS "  Static library:   ${RTTR_BUILD_STATIC}")
    message(STATUS "  Unit tests:       ${RTTR_BUILD_TESTS}")
    message(STATUS "  Examples:         ${RTTR_BUILD_EXAMPLES}")
    message(STATUS "  Benchmarks:       ${RTTR_BUILD_BENCHMARKS}")
    message(STATUS "  Documentation:    ${RTTR_BUILD_DOCUMENTATION}")
    message(STATUS "  C++ Standard:     ${CMAKE_CXX_STANDARD}")
    message(STATUS "  PCH enabled:      ${RTTR_USE_PCH}")
    message(STATUS "")
endif()