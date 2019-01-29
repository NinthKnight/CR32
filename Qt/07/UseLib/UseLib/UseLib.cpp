// UseLib.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Test/MyCalc.h"
#include <stdlib.h>

//工程中添加lib的方法
//#pragma comment(lib, R"(F:\CR32\repos\CR32\qt\07\UseLib\Test.lib)")

#pragma comment(lib, "Test.lib")


//extern "C" void TestC();

void Test123();

int main()
{
    //CMyCalc calc;
    //printf("%d", calc.add(1, 2));
    Test123();

    system("pause");

    return 0;
}

