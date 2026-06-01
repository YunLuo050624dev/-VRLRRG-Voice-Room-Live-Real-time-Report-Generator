# 接入C++ UI库

## 默认UI框架

**本项目默认使用原生 Win32 API。**

Win32 API 是微软为 Windows 提供的原生应用程序编程接口。它提供了对 Windows 操作系统功能的直接访问，适合轻量级、高性能的桌面应用程序。

### Win32 API 的优势
- 无需外部依赖
- 可执行文件体积小
- 直接访问 Windows 功能
- 完全控制 UI
- 卓越的性能

## 支持的 C++ UI 库

### 1. Qt

Qt 是一个用于开发图形用户界面的跨平台应用程序框架。

#### 集成步骤
1. 安装 Qt（从 [qt.io](https://www.qt.io/) 下载）
2. 修改 `CMakeLists.txt`：
```cmake
cmake_minimum_required(VERSION 3.15)
project(Voice-Room-Live-Real-time-Report-Generator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找 Qt
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

3. 使用 Qt 控件重写应用程序
4. 更新 `main.cpp` 以使用 `QApplication`

### 2. wxWidgets

wxWidgets 是一个 C++ 库，允许开发者为 Windows、macOS、Linux 和其他平台创建应用程序。

#### 集成步骤
1. 安装 wxWidgets
2. 修改 `CMakeLists.txt`：
```cmake
find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
```

### 3. Dear ImGui

Dear ImGui 是一个用于 C++ 的无臃肿图形用户界面库。

#### 集成步骤
1. 将 ImGui 源文件添加到项目中
2. 创建渲染后端（例如使用 DirectX 或 OpenGL）
3. 用 ImGui 渲染循环替换 Win32 消息循环

### 4. MFC（微软基础类）

MFC 是微软用于在 C++ 中开发 Windows 应用程序的库。

#### 集成步骤
1. 在 Visual Studio 项目设置中启用 MFC
2. 使用 `CWinApp` 和 `CDialog` 类替代 Win32 API

## 迁移考虑事项

### 何时考虑切换 UI 库
- 需要跨平台支持
- 希望使用现代 UI 组件
- 复杂的布局需求
- 需要内置的主题/样式功能

### 迁移检查清单
1. **备份代码** - 在进行重大更改之前始终创建备份
2. **规划迁移** - 将现有功能映射到新的 UI 框架
3. **增量测试** - 一次迁移一个功能并进行彻底测试
4. **更新文档** - 保持 README 和开发指南为最新

## 维护 Win32 API 选项

如果您希望保留使用 Win32 API 或其他 UI 库的选项，请考虑使用预处理器指令：

```cpp
#ifdef USE_QT
// Qt 实现
#else
// Win32 API 实现
#endif
```

并在 `CMakeLists.txt` 中：
```cmake
option(USE_QT "使用 Qt 框架而不是 Win32 API" OFF)

if(USE_QT)
    # Qt 配置
else()
    # Win32 配置
endif()
```

## 建议

- **对于本项目**：除非有特殊需求，否则继续使用 Win32 API
- **对于跨平台需求**：考虑使用 Qt 或 wxWidgets
- **对于快速原型开发**：考虑使用 Dear ImGui
- **对于企业级 Windows 应用**：考虑使用 MFC

## 其他资源

- [Win32 API 文档](https://learn.microsoft.com/zh-cn/windows/win32/)
- [Qt 文档](https://doc.qt.io/)
- [wxWidgets 文档](https://docs.wxwidgets.org/)
- [Dear ImGui GitHub](https://github.com/ocornut/imgui)
