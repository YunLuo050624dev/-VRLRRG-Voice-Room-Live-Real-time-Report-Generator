# 开发指南

## 架构概述

Voice-Room-Live-Real-time-Report-Generator 是使用 **原生 Win32 API** 和 C++ 构建的 Windows 桌面应用程序。它采用模块化设计，对话框实现分离。

> **注意**：本项目默认使用 Win32 API。关于接入其他 C++ UI 库（Qt、wxWidgets、Dear ImGui、MFC）的信息，请参阅 [UI库接入指南](ImportTheUILibrary_CN.md)。

## 项目结构

```
Voice-Room-Live-Real-time-Report-Generator/
├── Src/
│   ├── main.cpp              # 主窗口和应用程序逻辑
│   ├── DataStructures.h      # 数据结构和全局变量
│   ├── Resource.h            # 控件 ID 和常量
│   ├── TargetDialog.h/cpp    # 目标值设置对话框
│   └── TimePickerDialog.h/cpp # 时间选择对话框
└── CMakeLists.txt            # 构建配置
```

## 核心组件

### 1. 数据结构 (DataStructures.h)

#### CounterData
存储每个计数器（喊活、新付、拉新、建联、二消、三关）的信息：
```cpp
struct CounterData {
    HWND hCurrEdit;      // 当前值编辑框
    HWND hTgtEdit;       // 目标值编辑框
    int incBtnId;        // 增量按钮 ID
    int setBtnId;        // 设置按钮 ID
    int currValue;       // 当前值
    int tgtValue;        // 目标值
};
```

#### HostData
存储每个主持行的信息：
```cpp
struct HostData {
    HWND hLabel;         // 主持编号标签
    HWND hNameEdit;      // 主持名称编辑框
    HWND hLaxinEdit;     // 拉新数编辑框
    HWND hErxiaoEdit;    // 二消数编辑框
    HWND hJianlianEdit;  // 建联数编辑框
    HWND hSanguanEdit;   # 三关数编辑框
    // ... 其他控件
    int hostIndex;       # 主持索引
};
```

### 2. 资源定义 (Resource.h)

定义所有控件 ID：
- `MAX_HOSTS` - 最大主持数 (8)
- `BASE_HOST_COUNT` - 初始主持数 (3)
- 不同计数器类型和主持控件的控件 ID 范围

### 3. 主窗口 (main.cpp)

关键函数：
- `WndProc()` - 主窗口过程，处理所有消息
- `CreateLabel()`, `CreateEdit()`, `CreateButton()` - 创建控件的辅助函数
- `UpdateHostRows()` - 添加/删除主持时更新主持表格布局
- `CopyToClipboard()` - 将报表数据复制到剪贴板

消息处理：
- `WM_CREATE` - 初始化所有控件
- `WM_COMMAND` - 处理按钮点击和编辑框更改
- `WM_SIZE` - 处理窗口调整大小
- `WM_PAINT` - 绘制窗口背景

### 4. 目标对话框 (TargetDialog.h/cpp)

用于设置目标值的自定义对话框：
- 使用自定义窗口类 (`TargetDialogClass`)
- 功能：数字输入、确定/取消按钮
- 点击确定时更新对应的计数器

### 5. 时间选择对话框 (TimePickerDialog.h/cpp)

用于选择档位时间的对话框：
- 小时选择 (0-23)
- 分钟选择 (0-55，5分钟增量)
- 支持鼠标滚轮滚动
- 如果开始时间 > 结束时间，自动调整结束时间

## 添加新功能

### 添加新计数器

1. 在 `Resource.h` 中添加新控件 ID：
```cpp
#define ID_BTN_NEWCOUNTER_INC 2061
#define ID_BTN_NEWCOUNTER_SET 2062
#define ID_EDIT_NEWCOUNTER_CURR 2063
#define ID_EDIT_NEWCOUNTER_TGT 2064
```

2. 在 `main.cpp` 中扩展 `gCounters` 数组

3. 在 `WM_CREATE` 处理程序中添加控件创建

4. 在 `WM_COMMAND` 处理程序中添加命令处理

### 添加新对话框

1. 创建新的头文件和实现文件（例如 `MyDialog.h`、`MyDialog.cpp`）

2. 实现对话框过程：
```cpp
LRESULT CALLBACK MyDialogProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE:
            // 创建控件
            return 0;
        case WM_COMMAND:
            // 处理命令
            return 0;
        case WM_DESTROY:
            // 清理
            return 0;
    }
    return DefWindowProc(hDlg, msg, wParam, lParam);
}
```

3. 注册窗口类并在显示函数中创建对话框

4. 将新文件添加到 `CMakeLists.txt`

## 风格指南

- 使用 Win32 API 约定
- 遵循现有代码结构
- 保持函数专注和模块化
- 使用有意义的变量和函数名
- 为复杂逻辑添加注释

## 调试技巧

- 使用 `OutputDebugString()` 输出调试信息
- 检查 Win32 API 调用的返回值
- 使用 Spy++ 检查窗口消息
- 验证控件 ID 在创建和处理之间匹配

## 常见模式

### 创建控件

```cpp
CreateWindow(L"STATIC", L"标签", WS_CHILD | WS_VISIBLE,
    x, y, width, height, parent, NULL, hInstance, NULL);

CreateWindow(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
    x, y, width, height, parent, (HMENU)controlId, hInstance, NULL);

CreateWindow(L"BUTTON", L"按钮", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
    x, y, width, height, parent, (HMENU)controlId, hInstance, NULL);
```

### 处理 WM_COMMAND

```cpp
case WM_COMMAND:
    switch (LOWORD(wParam)) {
        case ID_MY_BUTTON:
            // 处理按钮点击
            break;
        case ID_MY_EDIT:
            if (HIWORD(wParam) == EN_CHANGE) {
                // 处理编辑框更改
            }
            break;
    }
    return 0;
```

## 构建配置

项目使用 CMake 进行构建。将新源文件添加到 `CMakeLists.txt`：

```cmake
add_executable(${PROJECT_NAME} WIN32 
    Src/main.cpp
    Src/TargetDialog.cpp
    Src/TimePickerDialog.cpp
    Src/MyNewDialog.cpp  # 在此添加新文件
)
```
