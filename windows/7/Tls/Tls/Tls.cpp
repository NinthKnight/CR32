// Tls.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h> 
#include <windows.h> 

#define THREADCOUNT 4 
DWORD dwTlsIndex;

VOID ErrorExit(LPTSTR);

VOID CommonFunc(VOID)
{
    LPVOID lpvData;

    // Retrieve a data pointer for the current thread. 

    lpvData = TlsGetValue(dwTlsIndex);
    if ((lpvData == 0) && (GetLastError() != 0))
        ErrorExit("TlsGetValue error");

    // Use the data stored for the current thread. 

    printf("common: thread %d: lpvData=%lx\n",
        GetCurrentThreadId(), lpvData);

    Sleep(5000);
}

DWORD WINAPI ThreadFunc(VOID)
{
    LPVOID lpvData;

    // Initialize the TLS index for this thread. 

    lpvData = (LPVOID)LocalAlloc(LPTR, 256);
    if (!TlsSetValue(dwTlsIndex, lpvData))
        ErrorExit("TlsSetValue error");

    printf("thread %d: lpvData=%lx\n", GetCurrentThreadId(), lpvData);

    CommonFunc();

    // Release the dynamic memory before the thread returns. 

    lpvData = TlsGetValue(dwTlsIndex);
    if (lpvData != 0)
        LocalFree((HLOCAL)lpvData);

    return 0;
}

DWORD main(VOID)
{
    DWORD IDThread;
    HANDLE hThread[THREADCOUNT];
    int i;

    // Allocate a TLS index. 

    if ((dwTlsIndex = TlsAlloc()) == -1)
        ErrorExit("TlsAlloc failed");

    // Create multiple threads. 

    for (i = 0; i < THREADCOUNT; i++)
    {
        hThread[i] = CreateThread(NULL, // no security attributes 
            0,                           // use default stack size 
            (LPTHREAD_START_ROUTINE)ThreadFunc, // thread function 
            NULL,                    // no thread function argument 
            0,                       // use default creation flags 
            &IDThread);              // returns thread identifier 

                                     // Check the return value for success. 
        if (hThread[i] == NULL)
            ErrorExit("CreateThread error\n");
    }

    for (i = 0; i < THREADCOUNT; i++)
        WaitForSingleObject(hThread[i], INFINITE);

    return 0;
}

VOID ErrorExit(LPTSTR lpszMessage)
{
    fprintf(stderr, "%s\n", lpszMessage);
    ExitProcess(0);
}
