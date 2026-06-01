#pragma once

#include <windows.h>
#include "DataStructures.h"

LRESULT CALLBACK TargetDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
void ShowTargetDialog(HWND hwnd, CounterData* pCounter);