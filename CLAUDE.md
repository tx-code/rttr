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

### Essential Commands

```bash
# Configure with Debug preset (includes examples and benchmarks)
cmake --preset debug

# Build Debug configuration  
cmake --build build/debug

# Configure and build Release
cmake --preset release
cmake --build build/release

# Run all unit tests (555 tests total)
cd build/debug && ctest

# Run unit tests directly with filtering
./build/debug/bin/unit_tests_d.exe "[method]"  # Run only method tests
./build/debug/bin/unit_tests_d.exe --list-tests  # List all available tests

# Run specific benchmark suites
./build/debug/bin/bench_method_d.exe      # Method invocation performance
./build/debug/bin/bench_variant_d.exe     # Variant operations performance  
./build/debug/bin/bench_rttr_cast_d.exe   # Type casting performance
```

### CMake Configuration

Key build options (set in CMakeUserPresets.json):
- `BUILD_EXAMPLES=ON`: JSON serialization, library loading, scripting examples
- `BUILD_BENCHMARKS=ON`: nanobench-based performance tests
- `BUILD_UNIT_TESTS=ON`: Catch2-based test suite (always enabled)
- `BUILD_DOCUMENTATION=ON`: Doxygen API docs

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
- **ChaiScript**: Embedded scripting language (`vcpkg install chaiscript`)

### Legacy Dependencies (Removed)
The modernization process removed bundled 3rd_party dependencies:
- ~~RapidJSON~~ → nlohmann::json
- ~~Nonius benchmarking~~ → nanobench  
- ~~Bundled Catch~~ → vcpkg Catch2

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

### Build Issues
- Ensure vcpkg toolchain path is correct in CMakeUserPresets.json
- Verify CMake version ≥ 3.21 with `cmake --version`
- Check Ninja availability with `ninja --version`
- For C++20 errors: ensure compiler supports C++20 (MSVC 2019+, GCC 10+, Clang 10+)

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