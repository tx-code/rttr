# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

# RTTR (Run Time Type Reflection) - Project Guide

## Project Overview

RTTR is a **modernized C++20 reflection library** that provides runtime type introspection and modification capabilities. This version has been upgraded from the original C++11/17 implementation to use modern CMake 3.21+ with vcpkg dependency management and C++20 standard compliance.

## Architecture Overview

### Core Reflection System
The RTTR architecture is built around several key abstractions working together:

- **`type`**: Central registry for runtime type information - handles type queries, creation, and metadata
- **`variant`**: Type-erased container that can hold any registered type with automatic conversions
- **`method`/`property`/`constructor`**: Reflection wrappers that enable runtime invocation of class members
- **Registration System**: Macro-based registration (`RTTR_REGISTRATION`) that populates the type system at static initialization

### Key Architecture Patterns

**Type System**: Uses a global type registry (`type_register`) with lazy initialization. Types are identified by `type_data*` pointers and support inheritance hierarchies through base class information.

**Pimpl Pattern**: Core classes use Pimpl (Pointer to Implementation) pattern to hide implementation details and maintain C++20 compatibility, especially for incomplete type handling in template contexts.

**Policy-Based Design**: Variant storage and type conversions use policy classes (`variant_data_base_policy`) to handle different storage strategies and conversion paths.

**Template Metaprogramming**: Extensive use of SFINAE and type traits for compile-time type introspection and registration validation.

## Build System

### Prerequisites
- CMake 3.21 or higher
- vcpkg package manager configured  
- Modern C++ compiler with C++20 support
- Ninja build system (recommended)

### Available Build Presets

**Clang-based presets (default):**
```bash
cmake --preset debug          # Debug build with Clang
cmake --preset release        # Release build with Clang  
cmake --preset relwithdebinfo # Release with debug info
cmake --preset minsizerel     # Minimum size release
cmake --preset debug-sanitizers # Debug with AddressSanitizer + UBSan
cmake --preset debug-static   # Debug with static library
```

**MSVC-based presets:**
```bash
# Option 1: Works in CLion IDE (automatic environment setup)
cmake --preset debug-msvc     # Debug build with MSVC cl
cmake --preset release-msvc   # Release build with MSVC cl

# Option 2: Command line - Use helper script (required for environment setup)
msvc_build.bat               # Configure and build debug with MSVC

# Option 3: Manual environment setup in Developer Command Prompt
# (Open "Developer Command Prompt for VS" first, then run cmake commands)
```

### Essential Commands

```bash
# Configure and build with default Clang preset
cmake --preset debug
cmake --build build/debug

# Build specific targets
cmake --build build/debug --target examples        # Build only examples
cmake --build build/debug --target unit_tests      # Build only unit tests
cmake --build build/debug --target bench_method_d.exe  # Build specific benchmark

# Run all unit tests (555 tests total - all currently passing)
cd build/debug && ctest
# OR run directly:
./build/debug/bin/unit_tests_d.exe

# Run unit tests with filtering
./build/debug/bin/unit_tests_d.exe "[method]"     # Run only method tests
./build/debug/bin/unit_tests_d.exe "[variant]"    # Run only variant tests
./build/debug/bin/unit_tests_d.exe --list-tests   # List all available tests

# Run specific benchmark suites
./build/debug/bin/bench_method_d.exe      # Method invocation performance
./build/debug/bin/bench_variant_d.exe     # Variant operations performance  
./build/debug/bin/bench_rttr_cast_d.exe   # Type casting performance

# Run examples
./build/debug/bin/json_example_d.exe              # JSON serialization demo
./build/debug/bin/library_loader_example_d.exe    # Plugin loading demo
```

### CMake Configuration (Modernized)

RTTR now uses **modern CMake 3.21+ best practices** with target-based configuration:

**Modern Build Options:**
```cmake
option(RTTR_BUILD_SHARED "Build shared library" ON)
option(RTTR_BUILD_STATIC "Build static library" OFF)  
option(RTTR_BUILD_TESTS "Build unit tests" ON)
option(RTTR_BUILD_EXAMPLES "Build examples" ON)
option(RTTR_BUILD_BENCHMARKS "Build benchmarks" ON)
option(RTTR_USE_PCH "Use precompiled headers" ON)
```

**Key Modern CMake Features:**
- **Target-based configuration**: All properties set via `target_*` commands  
- **Exported targets**: Use `RTTR::Core` for consumption via `find_package(rttr)`
- **Generator expressions**: Proper build/install interface separation
- **Component installation**: Runtime, Development, Documentation components
- **Version management**: Centralized in `project()` command
- **Clean build output**: Removed verbose scanning messages for better user experience

**Configuration Summary Display:**
```
RTTR 0.9.7 Configuration Summary:
  Build type:       Debug/Release
  Shared library:   ON/OFF
  Unit tests:       ON/OFF
  Examples:         ON/OFF
  Benchmarks:       ON/OFF
  C++ Standard:     20
```

The build system uses:
- **C++20 standard**: Enforced through CMake configuration
- **vcpkg integration**: All external dependencies managed through vcpkg
- **Ninja generator**: Configured for fast parallel builds
- **Separate build directories**: `build/debug/` and `build/release/`

## Dependencies

All dependencies are managed through vcpkg:

### Core Dependencies
- **Catch2**: Modern unit testing framework (`vcpkg install catch2`)
- **nanobench**: High-precision benchmarking (`vcpkg install nanobench`)
- **nlohmann-json**: JSON serialization for examples (`vcpkg install nlohmann-json`)

### Legacy Dependencies (Removed)
The modernization process removed bundled 3rd_party dependencies and unnecessary examples:
- ~~RapidJSON~~ → nlohmann::json
- ~~Nonius benchmarking~~ → nanobench  
- ~~Bundled Catch~~ → vcpkg Catch2
- ~~ChaiScript scripting example~~ → Removed (not needed for core functionality)

### Available Examples
- **json_serialization**: Demonstrates JSON serialization/deserialization using nlohmann::json
- **library_loading**: Shows dynamic library loading and plugin architecture

## Core RTTR Concepts

### Type Registration
Types must be explicitly registered before use:

```cpp
RTTR_REGISTRATION {
    rttr::registration::class_<MyClass>("MyClass")
        .constructor<>()
        .constructor<int, std::string>()
        .method("calculate", &MyClass::calculate)
        .property("value", &MyClass::m_value)
        .enumeration<MyEnum>("MyEnum")
            .value("OPTION_A", MyEnum::OPTION_A);
}
```

### Runtime Type Queries
```cpp
// Get type information
rttr::type t = rttr::type::get<MyClass>();
rttr::type t2 = rttr::type::get_by_name("MyClass");

// Iterate over reflected members
for (auto& prop : t.get_properties())
    std::cout << prop.get_name() << std::endl;

for (auto& method : t.get_methods())
    std::cout << method.get_name() << std::endl;
```

### Variant Usage (Type-Erased Storage)
```cpp
rttr::variant var = MyClass{};
if (var.get_type() == rttr::type::get<MyClass>()) {
    MyClass obj = var.get_value<MyClass>();
}

// Automatic conversions
rttr::variant num = 42;
std::string str = num.to_string();  // "42"
```

### Method Invocation
```cpp
MyClass obj;
rttr::method m = rttr::type::get(obj).get_method("calculate");
rttr::variant result = m.invoke(obj, arg1, arg2);
```

## Testing Architecture

### Unit Tests (555 tests)
- **Framework**: Catch2 with modern SECTION-based organization
- **Coverage**: All public APIs with positive/negative test cases
- **Organization**: Tests organized by component (`method/`, `variant/`, `constructor/`, etc.)
- **Plugin Testing**: Dynamic library loading tests in `plugin/` subdirectory

### Benchmark Tests
- **Framework**: nanobench (modern replacement for Nonius)
- **Suites**: Method invocation, variant operations, type casting performance
- **Output**: Detailed performance statistics with error margins and stability indicators
- **Comparison**: Native C++ vs RTTR reflection performance ratios

## Performance Characteristics

Based on benchmark results:
- **Method Finding**: RTTR ~20-35x slower than native dynamic_cast
- **Method Invocation**: RTTR ~11x slower than direct calls (simple types)
- **Type Casting**: RTTR ~2.5-4x slower than dynamic_cast  
- **Variant Operations**: RTTR ~2-3x slower than native conversions

These ratios are normal for reflection systems due to runtime type lookup and method resolution overhead.

## Development Patterns

### Modern CMake Integration
RTTR can now be consumed as a modern CMake package:

```cmake
# In your CMakeLists.txt
find_package(rttr REQUIRED)
target_link_libraries(my_app PRIVATE RTTR::Core)
# C++20 and include directories automatically propagated
```

**Available Targets:**
- `RTTR::Core` - Shared library (primary target)
- `RTTR::Core_Static` - Static library 
- `RTTR::Core_StaticRuntime` - Static runtime linking

### Adding New Reflection Features
1. Implement core functionality in `src/rttr/` 
2. Add corresponding wrapper class in `detail/` namespace
3. Update registration system in `registration.h`
4. Add comprehensive unit tests in `src/unit_tests/`
5. Update examples if the feature affects public API

### Template Metaprogramming Guidelines
- Use SFINAE patterns for type trait detection
- Leverage `std::enable_if_t` and `std::is_same_v` for template constraints
- Follow existing patterns in `detail/misc/misc_type_traits.h`
- Handle incomplete types using Pimpl pattern when necessary

### Memory Management
- RTTR uses shared ownership for type metadata (stored in global registry)
- Variant storage uses small object optimization with policy-based allocation
- All reflection objects are copyable value types wrapping shared implementation

## Troubleshooting

## Recent Changes and Current Status

### Project Status (2025-08)
- ✅ **All systems operational with Clang**: Examples, tests, and benchmarks compile and run successfully
- ✅ **555 unit tests passing**: Complete test coverage with 5043 assertions (using Clang build)
- ✅ **Clang build fully functional**: Default recommended build configuration
- ✅ **C++20 core_prerequisites.h simplified**: Removed ~50 lines of legacy code, modern static_assert checks
- ✅ **MSVC presets working**: Works in CLion IDE, command-line requires batch script for environment
- ✅ **Dependency cleanup**: Removed unnecessary ChaiScript example, streamlined dependencies
- ✅ **MSVC compatibility fixes**: Resolved `operator new[]` ambiguity and Clang pragma warnings
- ✅ **Helper scripts provided**: Batch scripts available for MSVC environment setup

### Modernization Summary

RTTR has been completely modernized from legacy CMake practices to follow current best practices:

### Completed Modernization Tasks
- ✅ **CMake 3.21+ Upgrade**: Full migration from CMake 2.8 to modern 3.21+ practices
- ✅ **Target-Based Configuration**: Eliminated all directory-level commands in favor of target-specific properties
- ✅ **Modern Option Naming**: Migrated from `BUILD_*` to `RTTR_*` prefix for consistency
- ✅ **Exported Targets**: Added proper `RTTR::Core` namespace support for `find_package`
- ✅ **Generator Expressions**: Proper build/install interface separation using `$<BUILD_INTERFACE>` and `$<INSTALL_INTERFACE>`
- ✅ **Version Management**: Centralized version info in main `project()` command
- ✅ **Clean Build Output**: Removed verbose "Scanning module" messages for better UX
- ✅ **Component Installation**: Organized into Runtime, Development, Documentation components
- ✅ **CMakePackageConfigHelpers**: Modern config file generation for downstream consumption
- ✅ **Modern CMake Policies**: Added CMP0167 policy to handle Boost module removal warnings
- ✅ **Multi-compiler CMake Presets**: Both Clang and MSVC configurations available
- ✅ **C++20 Code Simplification**: Removed RTTR_FORCE_INLINE macro, simplified pragma warnings, added static_assert compiler checks

### Build Issues
- **Modern CMake**: Requires CMake 3.21+ for modern features and policies
- **vcpkg integration**: Ensure vcpkg toolchain path is correct in CMakeUserPresets.json
- **Compiler support**: C++20 requires MSVC 2019+, GCC 10+, or Clang 10+
- **Ninja availability**: Check `ninja --version` - recommended for fast parallel builds
- **Option names**: Use modern `RTTR_*` options instead of legacy `BUILD_*` names
- **MSVC with Ninja**: Environment-dependent compilation
  - **✅ Works in CLion**: IDE automatically handles MSVC environment variables
  - **❌ Command line issue**: Requires manual environment setup via batch scripts or Developer Command Prompt
  - **Root cause**: MSVC compiler needs INCLUDE/LIB environment variables that are not set in regular shell
  - **Solution**: Use provided batch scripts or open "Developer Command Prompt for VS" before running cmake
  - **Recommended Approach**: Use Clang build (default) for command-line development, MSVC for IDE development
  - **Status**: MSVC presets are correctly configured - only environment setup differs between contexts

### Runtime Issues  
- **Registration not found**: Ensure `RTTR_REGISTRATION` block is in a compiled .cpp file
- **Type not found**: Verify type is registered and registration code is linked
- **Plugin loading fails**: Check library dependencies and symbol visibility
- **Performance issues**: Use Release builds - Debug builds are significantly slower

### Test Failures
Run specific test suites:
```bash
# Run only method-related tests
./unit_tests_d.exe "[method]"

# Run with verbose output
./unit_tests_d.exe -s  # Show successful tests
./unit_tests_d.exe -d yes  # Show duration
```