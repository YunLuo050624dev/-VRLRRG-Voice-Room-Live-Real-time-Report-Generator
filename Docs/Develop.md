# Development Guide

## Architecture Overview

Voice-Room-Live-Real-time-Report-Generator is a Windows desktop application built using **native Win32 API** and C++. It follows a modular design with separate dialog implementations.

> **Note**: This project uses Win32 API by default. For information about integrating other C++ UI libraries (Qt, wxWidgets, Dear ImGui, MFC), see the [UI Library Integration Guide](ImportTheUILibrary.md).

## Project Structure

```
Voice-Room-Live-Real-time-Report-Generator/
├── Src/
│   ├── main.cpp              # Main window and application logic
│   ├── DataStructures.h      # Data structures and global variables
│   ├── Resource.h            # Control IDs and constants
│   ├── TargetDialog.h/cpp    # Target value setting dialog
│   └── TimePickerDialog.h/cpp # Time selection dialog
└── CMakeLists.txt            # Build configuration
```

## Core Components

### 1. Data Structures (DataStructures.h)

#### CounterData
Stores information for each counter (calling, new payment, new user acquisition, connection, repeat purchase, three-way conversion):
```cpp
struct CounterData {
    HWND hCurrEdit;      // Current value edit box
    HWND hTgtEdit;       // Target value edit box
    int incBtnId;        // Increment button ID
    int setBtnId;        // Set button ID
    int currValue;       // Current value
    int tgtValue;        // Target value
};
```

#### HostData
Stores information for each host row:
```cpp
struct HostData {
    HWND hLabel;         // Host number label
    HWND hNameEdit;      // Host name edit box
    HWND hLaxinEdit;     // New user count edit box
    HWND hErxiaoEdit;    // Repeat purchase edit box
    HWND hJianlianEdit;  // Connection edit box
    HWND hSanguanEdit;   // Three-way conversion edit box
    // ... other controls
    int hostIndex;       // Host index
};
```

### 2. Resource Definitions (Resource.h)

Defines all control IDs:
- `MAX_HOSTS` - Maximum number of hosts (8)
- `BASE_HOST_COUNT` - Initial host count (3)
- Control ID ranges for different counter types and host controls

### 3. Main Window (main.cpp)

Key functions:
- `WndProc()` - Main window procedure, handles all messages
- `CreateLabel()`, `CreateEdit()`, `CreateButton()` - Helper functions for creating controls
- `UpdateHostRows()` - Updates host table layout when hosts are added/removed
- `CopyToClipboard()` - Copies report data to clipboard

Message handling:
- `WM_CREATE` - Initializes all controls
- `WM_COMMAND` - Handles button clicks and edit box changes
- `WM_SIZE` - Handles window resizing
- `WM_PAINT` - Draws window background

### 4. Target Dialog (TargetDialog.h/cpp)

Custom dialog for setting target values:
- Uses a custom window class (`TargetDialogClass`)
- Features: numeric input, OK/Cancel buttons
- Updates the corresponding counter when OK is clicked

### 5. Time Picker Dialog (TimePickerDialog.h/cpp)

Dialog for selecting shift times:
- Hour selection (0-23)
- Minute selection (0-55 in 5-minute increments)
- Mouse wheel support for scrolling
- Auto-adjusts end time if start time > end time

## Adding New Features

### Adding a New Counter

1. Add new control IDs in `Resource.h`:
```cpp
#define ID_BTN_NEWCOUNTER_INC 2061
#define ID_BTN_NEWCOUNTER_SET 2062
#define ID_EDIT_NEWCOUNTER_CURR 2063
#define ID_EDIT_NEWCOUNTER_TGT 2064
```

2. Extend the `gCounters` array in `main.cpp`

3. Add control creation in `WM_CREATE` handler

4. Add command handling in `WM_COMMAND` handler

### Adding a New Dialog

1. Create new header and implementation files (e.g., `MyDialog.h`, `MyDialog.cpp`)

2. Implement the dialog procedure:
```cpp
LRESULT CALLBACK MyDialogProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE:
            // Create controls
            return 0;
        case WM_COMMAND:
            // Handle commands
            return 0;
        case WM_DESTROY:
            // Cleanup
            return 0;
    }
    return DefWindowProc(hDlg, msg, wParam, lParam);
}
```

3. Register the window class and create the dialog in your show function

4. Add the new files to `CMakeLists.txt`

## Style Guidelines

- Use Win32 API conventions
- Follow the existing code structure
- Keep functions focused and modular
- Use meaningful variable and function names
- Add comments for complex logic

## Debugging Tips

- Use `OutputDebugString()` for debug output
- Check return values of Win32 API calls
- Use Spy++ to inspect window messages
- Verify control IDs match between creation and handling

## Common Patterns

### Creating Controls

```cpp
CreateWindow(L"STATIC", L"Label", WS_CHILD | WS_VISIBLE,
    x, y, width, height, parent, NULL, hInstance, NULL);

CreateWindow(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
    x, y, width, height, parent, (HMENU)controlId, hInstance, NULL);

CreateWindow(L"BUTTON", L"Button", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
    x, y, width, height, parent, (HMENU)controlId, hInstance, NULL);
```

### Handling WM_COMMAND

```cpp
case WM_COMMAND:
    switch (LOWORD(wParam)) {
        case ID_MY_BUTTON:
            // Handle button click
            break;
        case ID_MY_EDIT:
            if (HIWORD(wParam) == EN_CHANGE) {
                // Handle edit box change
            }
            break;
    }
    return 0;
```

## Build Configuration

The project uses CMake for building. Add new source files to `CMakeLists.txt`:

```cmake
add_executable(${PROJECT_NAME} WIN32 
    Src/main.cpp
    Src/TargetDialog.cpp
    Src/TimePickerDialog.cpp
    Src/MyNewDialog.cpp  # Add new files here
)
```
