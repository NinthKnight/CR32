// volatile.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

int foo(int argc) {

    return argc + 10;
}

//volatile 易变的
int main(int argc, char* argv[])
{
    volatile int n = 0;

    int* pN = const_cast<int*>(&n);
    //int* pN = (int*)(&n);
    printf("%p", pN);

    n = foo(argc);

    int k = 0;
    printf("%d", n);

    return 0;
}

