// TestThread.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
//线程


DWORD ThreadFunc(LPVOID lpParam) {

    //HANDLE hProcess = GetCurrentProcess();

    //HANDLE hThread = GetCurrentThread();

    //TerminateThread(hThread, 0);

    while (true) {
        OutputDebugStringA("ThreadFunc(LPVOID lpParam)");
        Sleep(1000);
    }

    return 0;
}

class CTest {
public:
    CTest() {
        OutputDebugStringA("CTest");
    }

    ~CTest() {
        OutputDebugStringA("~CTest");
    }

};

int main()
{
    CTest t;

    HANDLE hThread = CreateThread(
        NULL,
        0,
        (LPTHREAD_START_ROUTINE)ThreadFunc,
        NULL,
        CREATE_SUSPENDED, //挂起
        NULL);
          
    Sleep(1000);

    //SuspendThread(hThread);
    SuspendThread(hThread);

    ResumeThread(hThread);
    ResumeThread(hThread);

    //
    //ExitThread(0);

    //用于同步
    //被等待的对象的状态：

    //                线程      进程
    //1. 有信号        退出      退出
    //2. 无信号        没退出    没退出

    DWORD dwRet = WaitForSingleObject(hThread,
                        INFINITE);

    if (dwRet == WAIT_TIMEOUT) {
        //表示超时
        OutputDebugStringA("dwRet == WAIT_TIMEOUT");
    }
    else if (dwRet == WAIT_OBJECT_0) {
        OutputDebugStringA("dwRet == WAIT_OBJECT_0");

        DWORD dwExitCode = 0;
        GetExitCodeThread(hThread, &dwExitCode);

    }


    return 0;
}

