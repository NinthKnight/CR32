// Sync.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <windows.h>

int g_data = 0;
bool IsLocked = false;

//�¼�

HANDLE g_Event;



//ͬ��
DWORD ThreadFunc(LPVOID lpParam) {

    printf("ThreadFunc:A\r\n");
    SetEvent(g_Event);

    //for (size_t i = 0; i < 1000000; i++)
    //{   
    //    WaitForSingleObject(g_Event, INFINITE);
    //    g_data++; 
    //    SetEvent(g_Event);
    //    //����
    //}
    //

    return 0;
}

//WaitForSingleObject
//              �¼�
//���ź�         ִ��
//���ź�         ����

int main()
{

    //HANDLE hEvent = OpenEventA(EVENT_ALL_ACCESS,
    //          TRUE,
    //          "CR32_EVENT");

    //if (hEvent != NULL) {
    //    printf("�Ѿ���һ��Ӧ��ʵ��");
    //    return 0;
    //}

    SECURITY_ATTRIBUTES sa = {0};
    sa.bInheritHandle = TRUE;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);

    g_Event = CreateEventA(NULL,
                        FALSE,//�Զ��� �Զ���Ϊ���ź�
                        FALSE,// TRUE ���źţ� FALSE ���ź�
                        NULL);

    STARTUPINFOA si = { 0 };
    si.cb = sizeof(STARTUPINFOA);

    PROCESS_INFORMATION pi = { 0 };


    //�������ӽ���
    BOOL bRet = CreateProcessA(NULL,
    	           "sub.exe",
    	           NULL,
    	           NULL,
    	           FALSE,
    	           CREATE_NEW_CONSOLE,
    	           NULL,
    	           NULL,
    	           &si,
    	           &pi);

    HANDLE dwNewEnent = 0;

    bRet = DuplicateHandle(GetCurrentProcess(),
        g_Event,
        pi.hProcess,
        &dwNewEnent,
        0,
        FALSE,
        DUPLICATE_SAME_ACCESS);


    WaitForSingleObject(g_Event, INFINITE);
    printf("father Process exit\r\n");

    return 0;
    
    //WaitForSingleObject(g_Event, INFINITE);



    HANDLE hThread = CreateThread(
        NULL,
        0,
        (LPTHREAD_START_ROUTINE)ThreadFunc,
        NULL,
        0, //����
        NULL);
   
    WaitForSingleObject(g_Event, INFINITE);
    printf("ThreadFunc:B\r\n");
    
    //for (size_t i = 0; i < 1000000; i++)
    //{
    //    WaitForSingleObject(g_Event, INFINITE);
    //    g_data++;
    //    SetEvent(g_Event);
    //}
    //


    DWORD dwRet = WaitForSingleObject(hThread,
        INFINITE);

    printf("g_data = %d", g_data);

    system("pause");

    return 0;
}

