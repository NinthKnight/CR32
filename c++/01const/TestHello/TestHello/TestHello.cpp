// TestHello.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


typedef  int BOOL;
#define TRUE 1
#define FALSE 0

void foo_bool() {
    bool bRet = true;
    bRet = false;

    if (bRet) {

    }

    BOOL b = TRUE;
    b = FALSE;

    int nSize = sizeof(bool);
    nSize = sizeof(BOOL);

    //while (0)
    //{

    //}
}

//const
//常量--变量

//c语言中的常量
#define PI 3.14


int main()
{
    int k = 3;
    //c++中的常量
    const int n = k;
    int* pN = (int*)&n;
    //n = 1;
    *pN = 2;

    printf("const int n = %d\r\n", n);
     

    return 0;
}

