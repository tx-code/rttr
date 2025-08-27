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
# RTTR Core Library - Modern CMake Configuration
####################################################################################

project(rttr_core LANGUAGES CXX)

# Generate library version variables for backward compatibility
generateLibraryVersionVariables(${RTTR_VERSION_MAJOR} ${RTTR_VERSION_MINOR} ${RTTR_VERSION_PATCH}
                                "RTTR" "Copyright (c) 2014 - 2018 Axel Menzel <info@rttr.org>" "MIT License")

# Load source files using existing function
loadFolder("rttr" HPP_FILES SRC_FILES BUILD_INSTALLER)

####################################################################################
# Precompiled Headers Setup
####################################################################################

if(RTTR_USE_PCH)
    activate_precompiled_headers("detail/base/pch.h" SRC_FILES)
endif()

####################################################################################
# Define common target properties function
####################################################################################

function(configure_rttr_target target_name)
    # Set basic properties
    set_target_properties(${target_name} PROPERTIES
        VERSION ${RTTR_VERSION}
        SOVERSION ${RTTR_VERSION_MAJOR}
        DEBUG_POSTFIX ${RTTR_DEBUG_POSTFIX}
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN ON
    )
    
    # Set C++20 as a requirement
    target_compile_features(${target_name} PUBLIC cxx_std_20)
    
    # Set include directories with generator expressions
    target_include_directories(${target_name} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/../>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../>
        $<INSTALL_INTERFACE:include>
    )
    
    # Link system libraries
    target_link_libraries(${target_name} PRIVATE ${CMAKE_DL_LIBS})
    
    # Apply compiler warnings
    set_compiler_warnings(${target_name})
    
    # RTTI configuration - enable RTTI publicly for all consumers
    if(RTTR_BUILD_WITH_RTTI)
        if(MSVC)
            target_compile_options(${target_name} PUBLIC /GR)
        else()
            target_compile_options(${target_name} PUBLIC -frtti)
        endif()
    else()
        target_compile_definitions(${target_name} PRIVATE RTTR_NO_RTTI)
        if(MSVC)
            target_compile_options(${target_name} PUBLIC /GR-)
        else()
            target_compile_options(${target_name} PUBLIC -fno-rtti)
        endif()
    endif()
endfunction()

####################################################################################
# Shared Library Target
####################################################################################

if(RTTR_BUILD_SHARED)
    add_library(rttr_core SHARED ${UnityBuild} ${SRC_FILES} ${HPP_FILES})
    add_library(RTTR::Core ALIAS rttr_core)
    
    # Configure shared library specific properties
    target_compile_definitions(rttr_core PRIVATE RTTR_DLL_EXPORTS)
    target_compile_definitions(rttr_core PUBLIC RTTR_DLL)
    
    # Apply common configuration
    configure_rttr_target(rttr_core)
    
    # Set export name for find_package support
    set_target_properties(rttr_core PROPERTIES EXPORT_NAME Core)
    
    # Installation
    if(RTTR_BUILD_INSTALLER)
        install(TARGETS rttr_core 
                EXPORT rttr-targets
                RUNTIME DESTINATION ${RTTR_RUNTIME_INSTALL_DIR} COMPONENT Runtime
                LIBRARY DESTINATION ${RTTR_LIBRARY_INSTALL_DIR} COMPONENT Runtime  
                ARCHIVE DESTINATION ${RTTR_ARCHIVE_INSTALL_DIR} COMPONENT Development
                FRAMEWORK DESTINATION ${RTTR_FRAMEWORK_INSTALL_DIR} COMPONENT Runtime
        )
        
        # Install PDB files on Windows
        install_pdb_files(rttr_core)
    endif()
endif()

####################################################################################
# Static Library Target  
####################################################################################

if(RTTR_BUILD_STATIC)
    add_library(rttr_core_static STATIC ${UnityBuild} ${SRC_FILES} ${HPP_FILES})
    add_library(RTTR::Core_Static ALIAS rttr_core_static)
    
    # Apply common configuration
    configure_rttr_target(rttr_core_static)
    
    # Set export name and output name
    set_target_properties(rttr_core_static PROPERTIES 
        EXPORT_NAME Core_Static
        OUTPUT_NAME rttr_core
    )
    
    # Static libraries don't need DLL definitions
    target_compile_definitions(rttr_core_static PUBLIC RTTR_STATIC)
    
    # Installation
    if(RTTR_BUILD_INSTALLER)
        install(TARGETS rttr_core_static
                EXPORT rttr-targets  
                ARCHIVE DESTINATION ${RTTR_ARCHIVE_INSTALL_DIR} COMPONENT Development
        )
    endif()
endif()

####################################################################################
# Static Runtime Library Target (Legacy Support)
####################################################################################

if(RTTR_BUILD_WITH_STATIC_RUNTIME)
    add_library(rttr_core_static_runtime SHARED ${UnityBuild} ${SRC_FILES} ${HPP_FILES})
    add_library(RTTR::Core_StaticRuntime ALIAS rttr_core_static_runtime)
    
    # Configure as shared library with static runtime
    target_compile_definitions(rttr_core_static_runtime PRIVATE RTTR_DLL_EXPORTS)
    target_compile_definitions(rttr_core_static_runtime PUBLIC RTTR_DLL)
    
    # Apply common configuration
    configure_rttr_target(rttr_core_static_runtime)
    
    # Set export name
    set_target_properties(rttr_core_static_runtime PROPERTIES EXPORT_NAME Core_StaticRuntime)
    
    # Configure static runtime linking (compiler-specific)
    if(MSVC)
        target_compile_options(rttr_core_static_runtime PRIVATE 
            $<$<CONFIG:Debug>:/MTd>
            $<$<CONFIG:Release>:/MT>
            $<$<CONFIG:RelWithDebInfo>:/MT>
            $<$<CONFIG:MinSizeRel>:/MT>
        )
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_link_options(rttr_core_static_runtime PRIVATE ${GNU_STATIC_LINKER_FLAGS})
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        target_link_options(rttr_core_static_runtime PRIVATE ${CLANG_STATIC_LINKER_FLAGS})
    endif()
    
    # Installation
    if(RTTR_BUILD_INSTALLER)
        install(TARGETS rttr_core_static_runtime
                EXPORT rttr-targets
                RUNTIME DESTINATION ${RTTR_RUNTIME_INSTALL_DIR} COMPONENT Runtime
                LIBRARY DESTINATION ${RTTR_LIBRARY_INSTALL_DIR} COMPONENT Runtime
                ARCHIVE DESTINATION ${RTTR_ARCHIVE_INSTALL_DIR} COMPONENT Development
                FRAMEWORK DESTINATION ${RTTR_FRAMEWORK_INSTALL_DIR} COMPONENT Runtime
        )
        
        install_pdb_files(rttr_core_static_runtime)
    endif()
endif()

####################################################################################
# Header Installation
####################################################################################

if(RTTR_BUILD_INSTALLER)
    # Install headers preserving directory structure
    foreach(header_file ${HPP_FILES})
        get_filename_component(header_dir ${header_file} DIRECTORY)
        install(FILES ${header_file}
                DESTINATION "include/rttr/${header_dir}"
                COMPONENT Development
        )
    endforeach()
endif()

####################################################################################
# Summary (only show for main target)
####################################################################################