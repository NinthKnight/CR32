// inline.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "test.h"
//内联函数
// 1. inline是对编译器的建议
// 2. debug版本没有inline，为了方便调试
// 3. 内联函数必须写在头文件中

#define GETMAX(a, b) ((a) > (b) ? (a) : (b))

int main(int argc, char* argv[])
{
    foo();
    getMax(1, 2);

    //int n = argc;
    //int k = getMax(++n, 1);

    //printf("%d", k);
    //int k = a > b ? a : b;
    //GETMAX(++n, 1);

    //((++n) > (1) ? (++n) : (1))

    return 0;
}

