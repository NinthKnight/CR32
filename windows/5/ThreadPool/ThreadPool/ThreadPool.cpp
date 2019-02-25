// ThreadPool.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>

#include "MyThreadPool.h"

int main()
{
    //HANDLE hSem = CreateSemaphore(NULL,
    //          0,
    //          2,
    //          NULL);

    //ReleaseSemaphore(hSem, 1, NULL);

    //WaitForSingleObject(hSem, INFINITE);
    //WaitForSingleObject(hSem, INFINITE);
    CMyThreadPool pool;
    pool.Create();

    char buffer[20] = {0};

    for (int i = 0; i < 1000; i++) {
        memset(buffer, 0, 20);
        _itoa_s(i, buffer, 10);

        pool.addTask(buffer);
    }
    
    pool.Destroy();

    return 0;
}

