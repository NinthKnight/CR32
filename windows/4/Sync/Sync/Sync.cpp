// Sync.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <windows.h>

int g_data = 0;
bool IsLocked = false;

//�ٽ���

CRITICAL_SECTION g_cs;

//ͬ��
DWORD ThreadFunc(LPVOID lpParam) {

    for (size_t i = 0; i < 1000000; i++)
    {
        //g_data++;
        //����
        //InterlockedIncrement((unsigned long long *)&g_data);
        //������
        //while (InterlockedExchange((unsigned long long *)&IsLocked, true) == true) {
        //    Sleep(0);
        //}

        EnterCriticalSection(&g_cs);
        g_data++;
        LeaveCriticalSection(&g_cs);

        //InterlockedExchange((unsigned long long *)&IsLocked, false);


        //����
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
        0, //����
        NULL);
   
    for (size_t i = 0; i < 1000000; i++)
    {
        //g_data++;
        //����
        //InterlockedIncrement((unsigned long long *)&g_data);

        //while (InterlockedExchange((unsigned long long *)&IsLocked, true) == true) {
        //    Sleep(0);
        //}
        EnterCriticalSection(&g_cs);
        g_data++;
        LeaveCriticalSection(&g_cs);
        //InterlockedExchange((unsigned long long *)&IsLocked, false);

        //����
    }


    DWORD dwRet = WaitForSingleObject(hThread,
        INFINITE);

    printf("g_data = %d", g_data);


    DeleteCriticalSection(&g_cs);
    return 0;
}

