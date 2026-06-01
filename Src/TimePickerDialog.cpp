#include <stdio.h>
#include "TimePickerDialog.h"

HWND gTimePickerParent = NULL;
int gTimePickerEditId = 0;
HWND gTimePickerHourCombo = NULL;
HWND gTimePickerMinuteCombo = NULL;

LRESULT CALLBACK TimePickerWndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_CREATE: {
        CreateWindow(L"static", L"时：", WS_CHILD | WS_VISIBLE | SS_RIGHT,
            20, 20, 40, 25, hDlg, NULL, NULL, NULL);
        gTimePickerHourCombo = CreateWindow(L"combobox", NULL, 
            WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST,
            70, 20, 60, 500, hDlg, (HMENU)1001, NULL, NULL);
        
        CreateWindow(L"static", L"分：", WS_CHILD | WS_VISIBLE | SS_RIGHT,
            140, 20, 40, 25, hDlg, NULL, NULL, NULL);
        gTimePickerMinuteCombo = CreateWindow(L"combobox", NULL,
            WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST,
            190, 20, 60, 500, hDlg, (HMENU)1002, NULL, NULL);
        
        CreateWindow(L"button", L"确定", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            60, 60, 70, 25, hDlg, (HMENU)IDOK, NULL, NULL);
        CreateWindow(L"button", L"取消", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            140, 60, 70, 25, hDlg, (HMENU)IDCANCEL, NULL, NULL);
        
        for (int i = 0; i < 24; i++) {
            wchar_t hourStr[4];
            swprintf_s(hourStr, L"%02d", i);
            SendMessage(gTimePickerHourCombo, CB_ADDSTRING, 0, (LPARAM)hourStr);
        }
        
        for (int i = 0; i < 60; i += 5) {
            wchar_t minuteStr[4];
            swprintf_s(minuteStr, L"%02d", i);
            SendMessage(gTimePickerMinuteCombo, CB_ADDSTRING, 0, (LPARAM)minuteStr);
        }
        
        wchar_t currentTime[10];
        GetWindowText(GetDlgItem(gTimePickerParent, gTimePickerEditId), currentTime, 10);
        
        int hour = 0, minute = 0;
        swscanf_s(currentTime, L"%d:%d", &hour, &minute);
        
        SendMessage(gTimePickerHourCombo, CB_SETCURSEL, hour, 0);
        int minIdx = minute / 5;
        if (minIdx >= 12) minIdx = 11;
        SendMessage(gTimePickerMinuteCombo, CB_SETCURSEL, minIdx, 0);
        
        return 0;
    }
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK) {
            int hour = SendMessage(gTimePickerHourCombo, CB_GETCURSEL, 0, 0);
            int minuteIdx = SendMessage(gTimePickerMinuteCombo, CB_GETCURSEL, 0, 0);
            
            wchar_t timeStr[10];
            swprintf_s(timeStr, L"%02d:%02d", hour, minuteIdx * 5);
            SetWindowText(GetDlgItem(gTimePickerParent, gTimePickerEditId), timeStr);
            
            // 时间验证：如果开始时间大于结束时间，把结束时间设置为开始时间
            // ID_EDIT_TIMESTART = 1003, ID_EDIT_TIMEEND = 1004
            if (gTimePickerEditId == 1003) { // 开始时间
                wchar_t endTimeStr[10];
                GetWindowText(GetDlgItem(gTimePickerParent, 1004), endTimeStr, 10);
                int endHour = 0, endMin = 0;
                swscanf_s(endTimeStr, L"%d:%d", &endHour, &endMin);
                
                if (hour > endHour || (hour == endHour && (minuteIdx * 5) > endMin)) {
                    // 开始时间大于结束时间，把结束时间也设置为开始时间
                    SetWindowText(GetDlgItem(gTimePickerParent, 1004), timeStr);
                }
            } else if (gTimePickerEditId == 1004) { // 结束时间
                wchar_t startTimeStr[10];
                GetWindowText(GetDlgItem(gTimePickerParent, 1003), startTimeStr, 10);
                int startHour = 0, startMin = 0;
                swscanf_s(startTimeStr, L"%d:%d", &startHour, &startMin);
                
                if (startHour > hour || (startHour == hour && startMin > (minuteIdx * 5))) {
                    // 结束时间小于开始时间，把结束时间设置为开始时间
                    wchar_t newEndTimeStr[10];
                    swprintf_s(newEndTimeStr, L"%02d:%02d", startHour, startMin);
                    SetWindowText(GetDlgItem(gTimePickerParent, 1004), newEndTimeStr);
                }
            }
            
            DestroyWindow(hDlg);
            return 0;
        }
        if (LOWORD(wParam) == IDCANCEL) {
            DestroyWindow(hDlg);
            return 0;
        }
        break;
    case WM_MOUSEWHEEL: {
        HWND hFocus = GetFocus();
        if (hFocus == gTimePickerHourCombo || hFocus == gTimePickerMinuteCombo) {
            int current = SendMessage(hFocus, CB_GETCURSEL, 0, 0);
            int count = SendMessage(hFocus, CB_GETCOUNT, 0, 0);
            int delta = GET_WHEEL_DELTA_WPARAM(wParam);
            
            if (delta > 0) {
                current = (current - 1 < 0) ? 0 : current - 1;
            } else {
                current = (current + 1 >= count) ? count - 1 : current + 1;
            }
            
            SendMessage(hFocus, CB_SETCURSEL, current, 0);
            return 0;
        }
        break;
    }
    case WM_DESTROY:
        return 0;
    }
    return DefWindowProc(hDlg, message, wParam, lParam);
}

void ShowTimePickerDialog(HWND hwnd, int editId) {
    gTimePickerParent = hwnd;
    gTimePickerEditId = editId;
    
    WNDCLASS wc = {0};
    wc.lpfnWndProc = TimePickerWndProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = L"TimePickerDialog";
    RegisterClass(&wc);
    
    HWND hDlg = CreateWindow(L"TimePickerDialog", L"选择时间", 
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, 280, 120,
        hwnd, NULL, GetModuleHandle(NULL), NULL);
    
    if (hDlg) {
        ShowWindow(hDlg, SW_SHOW);
    }
}