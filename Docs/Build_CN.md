# 编译指南

## 前置要求

- MinGW-w64（包含 gcc, g++, mingw32-make）
- CMake 3.15 或更高版本

## 编译步骤

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

## 清理编译产物

```cmd
rd /s /q build
rd /s /q Out
```

## 输出

编译成功后，可执行文件位于 `Out/Voice-Room-Live-Real-time-Report-Generator.exe`

## 可移植性

项目完全可移植。您可以将整个项目目录移动到任何位置，无需修改任何配置文件。所有路径都使用 CMake 相对路径配置。
