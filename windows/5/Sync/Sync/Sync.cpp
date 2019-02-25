// Sync.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>

int g_data = 0;
bool IsLocked = false;

//事件

HANDLE g_Event;



//同步
DWORD ThreadFunc(LPVOID lpParam) {

    printf("ThreadFunc:A\r\n");
    SetEvent(g_Event);

    //for (size_t i = 0; i < 1000000; i++)
    //{   
    //    WaitForSingleObject(g_Event, INFINITE);
    //    g_data++; 
    //    SetEvent(g_Event);
    //    //解锁
    //}
    //

    return 0;
}

//WaitForSingleObject
//              事件
//有信号         执行
//无信号         阻塞

int main()
{

    //HANDLE hEvent = OpenEventA(EVENT_ALL_ACCESS,
    //          TRUE,
    //          "CR32_EVENT");

    //if (hEvent != NULL) {
    //    printf("已经打开一个应用实例");
    //    return 0;
    //}

    SECURITY_ATTRIBUTES sa = {0};
    sa.bInheritHandle = TRUE;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);

    g_Event = CreateEventA(NULL,
                        FALSE,//自动， 自动变为无信号
                        FALSE,// TRUE 有信号， FALSE 无信号
                        NULL);

    STARTUPINFOA si = { 0 };
    si.cb = sizeof(STARTUPINFOA);

    PROCESS_INFORMATION pi = { 0 };


    //创建儿子进程
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
        0, //挂起
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

