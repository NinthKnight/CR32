// Sync.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <windows.h>

int g_data = 0;
bool IsLocked = false;

//������

HANDLE g_Mutex;

//ͬ��
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
//              �¼�
//���ź�         ִ��
//���ź�         ����

int main()
{

    g_Mutex = CreateMutexA(NULL,
                        FALSE,//��ǰ�����߳��Ƿ�ռ�иû�����     
                        NULL);

    HANDLE hThread = CreateThread(
        NULL,
        0,
        (LPTHREAD_START_ROUTINE)ThreadFunc,
        NULL,
        0, //����
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

