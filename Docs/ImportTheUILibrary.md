# Importing C++ UI Libraries

## Default UI Framework

**This project uses native Win32 API by default.**

The Win32 API is Microsoft's native application programming interface for Windows. It provides direct access to Windows operating system features and is suitable for lightweight, high-performance desktop applications.

### Advantages of Win32 API
- No external dependencies required
- Small executable size
- Direct access to Windows features
- Full control over the UI
- Excellent performance

## Supported C++ UI Libraries

### 1. Qt

Qt is a cross-platform application framework for developing graphical user interfaces.

#### Integration Steps
1. Install Qt (download from [qt.io](https://www.qt.io/))
2. Modify `CMakeLists.txt`:
```cmake
cmake_minimum_required(VERSION 3.15)
project(Voice-Room-Live-Real-time-Report-Generator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Out)

add_executable(${PROJECT_NAME}
    Src/main.cpp
    Src/TargetDialog.cpp
    Src/TimePickerDialog.cpp
)

target_link_libraries(${PROJECT_NAME}
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)
```

3. Rewrite the application using Qt widgets
4. Update `main.cpp` to use `QApplication`

### 2. wxWidgets

wxWidgets is a C++ library that lets developers create applications for Windows, macOS, Linux and other platforms.

#### Integration Steps
1. Install wxWidgets
2. Modify `CMakeLists.txt`:
```cmake
find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
```

### 3. Dear ImGui

Dear ImGui is a bloat-free graphical user interface library for C++.

#### Integration Steps
1. Add ImGui source files to your project
2. Create a render backend (e.g., using DirectX or OpenGL)
3. Replace the Win32 message loop with ImGui rendering loop

### 4. MFC (Microsoft Foundation Classes)

MFC is a Microsoft library for developing Windows applications in C++.

#### Integration Steps
1. Enable MFC in Visual Studio project settings
2. Use `CWinApp` and `CDialog` classes instead of Win32 API

## Migration Considerations

### When to Consider Switching UI Libraries
- Need for cross-platform support
- Desire for modern UI components
- Complex layout requirements
- Need for built-in theming/styling

### Migration Checklist
1. **Back up your code** - Always create a backup before major changes
2. **Plan the migration** - Map existing features to the new UI framework
3. **Test incrementally** - Migrate one feature at a time and test thoroughly
4. **Update documentation** - Keep README and development guides current

## Maintaining Win32 API Option

If you want to maintain the option to use either Win32 API or another UI library, consider using preprocessor directives:

```cpp
#ifdef USE_QT
// Qt implementation
#else
// Win32 API implementation
#endif
```

And in `CMakeLists.txt`:
```cmake
option(USE_QT "Use Qt framework instead of Win32 API" OFF)

if(USE_QT)
    # Qt configuration
else()
    # Win32 configuration
endif()
```

## Recommendations

- **For this project**: Continue using Win32 API unless specific needs require otherwise
- **For cross-platform needs**: Consider Qt or wxWidgets
- **For rapid prototyping**: Consider Dear ImGui
- **For enterprise Windows apps**: Consider MFC

## Additional Resources

- [Win32 API Documentation](https://learn.microsoft.com/en-us/windows/win32/)
- [Qt Documentation](https://doc.qt.io/)
- [wxWidgets Documentation](https://docs.wxwidgets.org/)
- [Dear ImGui GitHub](https://github.com/ocornut/imgui)
