// HelloConsole.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include <windows.h>


//Ӧ�ó���ʵ�����
int WINAPI WinMain(HINSTANCE hInstance,      // handle to current instance
    HINSTANCE hPrevInstance,  // handle to previous instance
    LPSTR lpCmdLine,          // command line
    int nCmdShow)             // show state
{
    //LPTSTR lpWCmdLine = GetCommandLine();

    //LPWSTR* pStrAry = CommandLineToArgvW(lpWCmdLine, pCount);

    DWORD dwError = GetLastError();

    //HWND    hWnd = (HWND)0x00020E22;
    HANDLE h;

    //LPCTSTR lpContent = _T("World");
    //LPCTSTR lpCap = _T("Hello");
    UINT nType = MB_OKCANCEL;

    INT nRet = MessageBoxA(nullptr, "Hello", "World", nType);
    if (nRet == IDOK)
    {

    }



    return 0;
}

