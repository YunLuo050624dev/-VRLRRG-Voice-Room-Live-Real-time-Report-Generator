# Build Guide

## Prerequisites

- MinGW-w64 (includes gcc, g++, mingw32-make)
- CMake 3.15 or higher

## Build Steps

### Windows (MinGW)

```cmd
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
mingw32-make
```

### Windows (Visual Studio)

```cmd
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

## Clean Build Artifacts

```cmd
rd /s /q build
rd /s /q Out
```

## Output

After successful build, the executable is located at `Out/Voice-Room-Live-Real-time-Report-Generator.exe`

## Portability

The project is fully portable. You can move the entire project directory to any location without modifying any configuration files. All paths are configured using CMake relative paths.
