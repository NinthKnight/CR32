// homework1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>      /* printf */
#include <ctime>       /* time_t, time, ctime */
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <windows.h>


void foo(char* psz) {

    assert(psz != NULL);

    if (psz == NULL) {
        return;
    }

    psz[0] = 1;
}

int main(int argc, char* argv[])
{
    time_t t;
    //time(&t);
    t = time(nullptr);

    char szBuf[1] = { 0 };

    //断言,用于调试
    //assert(argc > 1);

    //errno_t err = ctime_s(NULL, 0, &t);
    int n2 = (*_errno());

    DWORD dwRet = GetLastError();

    FILE * pFile;
    pFile = fopen("unexist.ent", "r");
    if (pFile == NULL)
    { 
        int n1 = (*_errno());
        dwRet = GetLastError();
        printf("Error opening file unexist.ent: %s\n", strerror(errno));
    }
    return 0;



    return 0;
}

