// Hook.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <sstream>
#include <string>
#include <stdlib.h>
using namespace std;

HHOOK g_hHook;

LRESULT CALLBACK KeyboardProc(int code,       // hook code
    WPARAM wParam,  // virtual-key code
    LPARAM lParam   // keystroke-message information
    ) {

    int nKey = (int)wParam;
    stringstream ss;
    ss << nKey << "pressed" << endl;
    OutputDebugStringA(ss.str().c_str());

    return CallNextHookEx(g_hHook, code, wParam, lParam);
}

void SetHook() {
    //本地钩子
    g_hHook = SetWindowsHookEx(WH_KEYBOARD,
        KeyboardProc,
        NULL,
        0);

}


//int main()
//{
//    SetHook();
//
//
//    while (true)
//    {
//        Sleep(1);
//    }
//    
//    return 0;
//}

