# RTTR (Run Time Type Reflection) - Project Guide

## Project Overview

RTTR is a C++17 reflection library that provides runtime type introspection and modification capabilities. This modernized version uses CMake 3.21+ with vcpkg for dependency management.

## Architecture

### Core Components
- **Core Library** (`src/rttr/`): Main reflection implementation with type system, variant handling, and metadata management
- **Unit Tests** (`src/unit_tests/`): Comprehensive test suite using Catch2 framework  
- **Examples** (`src/examples/`): Demonstrates JSON serialization, library loading, and scripting integration
- **Benchmarks** (`src/benchmarks/`): Performance testing for methods, variants, and type casting
- **Documentation** (`doc/`): Doxygen-generated API documentation with custom styling

### Key Features
- Runtime type registration and query system
- Variant type for type-erased value storage
- Method and property reflection with access control
- Constructor/destructor reflection
- Enumeration support with conversion capabilities
- Template metaprogramming utilities
- Plugin system for dynamic library loading

## Build System

### Prerequisites
- CMake 3.21 or higher
- vcpkg package manager
- Modern C++ compiler with C++17 support
- Ninja build system (recommended)

### Build Commands

```bash
# Configure with CMake preset (Debug)
cmake --preset debug

# Build Debug configuration
cmake --build build/debug

# Configure and build Release
cmake --preset release
cmake --build build/release

# Run unit tests
cd build/debug && ctest
# Or run tests executable directly
./build/debug/src/unit_tests/unit_tests
```

### CMake Configuration

Current configuration uses modern CMake practices:
- Minimum version: 3.21
- C++17 standard enforcement
- vcpkg integration for dependency management
- Ninja generator for fast builds
- Separate debug/release build directories

Key CMake options:
- `BUILD_UNIT_TESTS=ON`: Build test suite (default)
- `BUILD_EXAMPLES=ON`: Build example projects
- `BUILD_BENCHMARKS=OFF`: Build performance tests
- `BUILD_DOCUMENTATION=ON`: Generate Doxygen docs

## Dependencies

All dependencies managed through vcpkg:

### Core Dependencies
- **Catch2**: Modern unit testing framework
  ```bash
  vcpkg install catch2
  ```

### Legacy Dependencies (bundled in 3rd_party/)
- ChaiScript: Embedded scripting language
- RapidJSON: JSON parsing library  
- Nonius: Benchmarking framework

Note: Legacy dependencies are gradually being replaced with vcpkg-managed versions.

## Development Workflow

### Code Standards
- C++17 standard compliance
- Modern CMake best practices
- Comprehensive unit test coverage
- Doxygen documentation for public APIs
- Clang warning compliance with strict error handling

### Common Tasks

#### Adding New Features
1. Implement core functionality in `src/rttr/`
2. Add corresponding unit tests in `src/unit_tests/`
3. Update examples if needed
4. Run full test suite to ensure compatibility

#### Working with Types
```cpp
// Register new types
RTTR_REGISTRATION {
    registration::class_<MyClass>("MyClass")
        .constructor<>()
        .method("myMethod", &MyClass::myMethod)
        .property("myField", &MyClass::myField);
}

// Query type information
type t = type::get<MyClass>();
for (auto& method : t.get_methods()) {
    std::cout << method.get_name() << std::endl;
}
```

#### Variant Usage
```cpp
variant v = MyClass{};
if (v.is_type<MyClass>()) {
    auto& obj = v.get_value<MyClass>();
    // Work with object
}
```

### Testing
- All public APIs must have corresponding unit tests
- Tests organized by component (constructor/, method/, variant/, etc.)
- Use Catch2 modern syntax with SECTION blocks
- Test both positive and negative cases

### Known Compiler Warnings (Fixed)
- Microsoft friend declaration warnings (qualified with namespace)
- Clang numeric conversion warnings (suppressed with pragmas)
- Function pointer comparison warnings (suppressed for valid use cases)
- Self-assignment warnings in test code (intentionally suppressed)

## Project Structure

```
rttr/
├── CMakeLists.txt              # Main build configuration
├── CMakeUserPresets.json       # Build presets (debug/release)
├── src/
│   ├── rttr/                   # Core reflection library
│   │   ├── type.h/.cpp         # Type system implementation
│   │   ├── variant.h/.cpp      # Type-erased value container
│   │   ├── registration.h      # Type registration macros
│   │   └── detail/             # Internal implementation details
│   ├── unit_tests/             # Comprehensive test suite
│   ├── examples/               # Usage demonstrations
│   └── benchmarks/             # Performance testing
├── doc/                        # Documentation generation
├── 3rd_party/                  # Legacy bundled dependencies
└── build/                      # Generated build directories
    ├── debug/                  # Debug build output
    └── release/                # Release build output
```

## Troubleshooting

### Build Issues
- Ensure vcpkg is properly configured in CMakeUserPresets.json
- Verify CMake version is 3.21+
- Check that Ninja is available in PATH

### Test Failures
- Run specific test cases: `./unit_tests [test_name]`
- Enable verbose output: `ctest --verbose`
- Check for ABI compatibility issues between debug/release builds

### Performance Considerations
- RTTR uses template metaprogramming extensively
- Compilation times can be significant for large codebases
- Consider using precompiled headers (USE_PCH=ON) for faster builds
- Release builds show significant performance improvements over debug

## Contributing

When making changes:
1. Follow existing code style and conventions
2. Add unit tests for new functionality
3. Update documentation for public API changes
4. Ensure all tests pass before committing
5. Use semantic commit messages describing the change