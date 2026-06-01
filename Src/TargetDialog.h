/*
Copyright 2026 YunLuo
Licensed under the Apache License, Version 2.0
http://www.apache.org/licenses/LICENSE-2.0
*/
#pragma once

#include <windows.h>
#include "DataStructures.h"

LRESULT CALLBACK TargetDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
void ShowTargetDialog(HWND hwnd, CounterData* pCounter);