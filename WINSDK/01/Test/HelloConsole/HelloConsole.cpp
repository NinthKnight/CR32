// HelloConsole.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>

int Test() {

    printf("123");
    return EXCEPTION_CONTINUE_EXECUTION;
}

//应用程序实例句柄
int WINAPI WinMain(HINSTANCE hInstance,      // handle to current instance
    HINSTANCE hPrevInstance,  // handle to previous instance
    LPSTR lpCmdLine,          // command line
    int nCmdShow)             // show state
{
    //api 
    int nCount;

    int* pCount = (int*)0x00000001;
    //ERROR_SUCCESS

    __try {
        BOOL bRet = IsBadReadPtr(pCount, 4);
    }
    __finally  {
        
    
    }
    


    LPTSTR lpWCmdLine = GetCommandLine();

    LPWSTR* pStrAry = CommandLineToArgvW(lpWCmdLine, pCount);

    DWORD dwError = GetLastError();

    HWND    hWnd = (HWND)0x00020E22;
    HANDLE h;

    LPCTSTR lpContent = _T("World");
    LPCTSTR lpCap = _T("Hello");
    UINT nType = MB_OKCANCEL;

    INT nRet = MessageBoxA(hWnd, "Hello", "World", nType);
    if (nRet == IDOK)
    {

    }



    return 0;
}

