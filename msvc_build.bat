@echo off
REM MSVC Build Helper - Sets up environment and builds
echo Setting up MSVC environment...
call "D:\Software\Visual Studio\VC\Auxiliary\Build\vcvarsall.bat" x64 >nul 2>&1

echo Configuring and building RTTR with MSVC...
cmake --preset debug-msvc && cmake --build build/debug-msvc

echo.
echo Build complete! Run tests with:
echo   build\debug-msvc\bin\unit_tests_d.exe