// TestThread.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <windows.h>
//�߳�


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
        CREATE_SUSPENDED, //����
        NULL);
          
    Sleep(1000);

    //SuspendThread(hThread);
    SuspendThread(hThread);

    ResumeThread(hThread);
    ResumeThread(hThread);

    //
    //ExitThread(0);

    //����ͬ��
    //���ȴ��Ķ����״̬��

    //                �߳�      ����
    //1. ���ź�        �˳�      �˳�
    //2. ���ź�        û�˳�    û�˳�

    DWORD dwRet = WaitForSingleObject(hThread,
                        INFINITE);

    if (dwRet == WAIT_TIMEOUT) {
        //��ʾ��ʱ
        OutputDebugStringA("dwRet == WAIT_TIMEOUT");
    }
    else if (dwRet == WAIT_OBJECT_0) {
        OutputDebugStringA("dwRet == WAIT_OBJECT_0");

        DWORD dwExitCode = 0;
        GetExitCodeThread(hThread, &dwExitCode);

    }


    return 0;
}

