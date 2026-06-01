#include <string>
#include "TargetDialog.h"
#include "DataStructures.h"
#include "Resource.h"

static HWND gTargetDlg = NULL;
static CounterData* gpCounter = NULL;

LRESULT CALLBACK TargetDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE: {
        // 创建控件
        CreateWindow(L"static", L"设定目标值：", WS_CHILD | WS_VISIBLE,
            20, 20, 120, 20, hDlg, NULL, NULL, NULL);
        
        CreateWindow(L"edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
            140, 18, 100, 25, hDlg, (HMENU)1001, NULL, NULL);
        
        CreateWindow(L"button", L"确认", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            20, 60, 100, 30, hDlg, (HMENU)IDOK, NULL, NULL);
        
        CreateWindow(L"button", L"取消", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            140, 60, 100, 30, hDlg, (HMENU)IDCANCEL, NULL, NULL);
        
        // 设置初始值
        SetWindowText(GetDlgItem(hDlg, 1001), std::to_wstring(gpCounter->tgtValue).c_str());
        return 0;
    }
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK) {
            wchar_t buf[32];
            GetWindowText(GetDlgItem(hDlg, 1001), buf, 32);
            gpCounter->tgtValue = _wtoi(buf);
            SetWindowText(gpCounter->hTgtEdit, std::to_wstring(gpCounter->tgtValue).c_str());
            DestroyWindow(hDlg);
            gTargetDlg = NULL;
        } else if (LOWORD(wParam) == IDCANCEL) {
            DestroyWindow(hDlg);
            gTargetDlg = NULL;
        }
        return 0;
    case WM_DESTROY:
        gTargetDlg = NULL;
        return 0;
    }
    return DefWindowProc(hDlg, uMsg, wParam, lParam);
}

void ShowTargetDialog(HWND hwnd, CounterData* pCounter) {
    if (gTargetDlg) {
        SetForegroundWindow(gTargetDlg);
        return;
    }
    
    gpCounter = pCounter;
    
    // 注册窗口类
    WNDCLASS wc = {0};
    wc.lpfnWndProc = TargetDlgProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = L"TargetDialogClass";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    RegisterClass(&wc);
    
    // 创建窗口
    gTargetDlg = CreateWindow(L"TargetDialogClass", L"设定目标", 
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, 280, 130,
        hwnd, NULL, GetModuleHandle(NULL), NULL);
    
    if (gTargetDlg) {
        ShowWindow(gTargetDlg, SW_SHOW);
    }
}