// Sync.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>

int g_data = 0;
bool IsLocked = false;

//互斥体

HANDLE g_Mutex;

//同步
DWORD ThreadFunc(LPVOID lpParam) {

    for (size_t i = 0; i < 1000000; i++)
    {
        //WaitForSingleObject(g_Mutex, INFINITE);

        g_data++;
        //ReleaseMutex(g_Mutex);
    }

    WaitForSingleObject(g_Mutex, INFINITE);


    return 0;
}

//WaitForSingleObject
//              事件
//有信号         执行
//无信号         阻塞

int main()
{

    g_Mutex = CreateMutexA(NULL,
                        FALSE,//当前调用线程是否占有该互斥体     
                        NULL);

    HANDLE hThread = CreateThread(
        NULL,
        0,
        (LPTHREAD_START_ROUTINE)ThreadFunc,
        NULL,
        0, //挂起
        NULL);
   
    DWORD dwRet = WaitForSingleObject(hThread,
        INFINITE);

    dwRet = WaitForSingleObject(g_Mutex, INFINITE);

    //WAIT_ABANDONED
    
    //for (size_t i = 0; i < 1000000; i++)
    //{
    //    WaitForSingleObject(g_Mutex, INFINITE);

    //    g_data++;
    //    ReleaseMutex(g_Mutex);
    //}
    
    printf("g_data = %d", g_data);

    system("pause");

    return 0;
}

