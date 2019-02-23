// Sync.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>

int g_data = 0;
bool IsLocked = false;

//临界区

CRITICAL_SECTION g_cs;

//同步
DWORD ThreadFunc(LPVOID lpParam) {

    for (size_t i = 0; i < 1000000; i++)
    {
        //g_data++;
        //上锁
        //InterlockedIncrement((unsigned long long *)&g_data);
        //自旋锁
        //while (InterlockedExchange((unsigned long long *)&IsLocked, true) == true) {
        //    Sleep(0);
        //}

        EnterCriticalSection(&g_cs);
        g_data++;
        LeaveCriticalSection(&g_cs);

        //InterlockedExchange((unsigned long long *)&IsLocked, false);


        //解锁
    }

    return 0;
}



int main()
{
    InitializeCriticalSection(&g_cs);

    HANDLE hThread = CreateThread(
        NULL,
        0,
        (LPTHREAD_START_ROUTINE)ThreadFunc,
        NULL,
        0, //挂起
        NULL);
   
    for (size_t i = 0; i < 1000000; i++)
    {
        //g_data++;
        //上锁
        //InterlockedIncrement((unsigned long long *)&g_data);

        //while (InterlockedExchange((unsigned long long *)&IsLocked, true) == true) {
        //    Sleep(0);
        //}
        EnterCriticalSection(&g_cs);
        g_data++;
        LeaveCriticalSection(&g_cs);
        //InterlockedExchange((unsigned long long *)&IsLocked, false);

        //解锁
    }


    DWORD dwRet = WaitForSingleObject(hThread,
        INFINITE);

    printf("g_data = %d", g_data);


    DeleteCriticalSection(&g_cs);
    return 0;
}

