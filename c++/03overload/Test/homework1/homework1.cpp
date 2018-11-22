// homework1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <ctime>

using namespace std;
inline void f1()
{
    clock_t t = clock();
}

void f2()
{
    clock_t t = clock();
}

int main()
{
        clock_t st = NULL;
        clock_t et = NULL;

        char szBuf[50] = { 0 };
        //st = clock();
        //for (int i = 0; i < 1000000; i++)
        //{
        //    for (int k = 0; k < 10; k++) {
        //        f2();
        //    }
        //}

        //et = clock() - st;
        //cout << "f2() : " << et << endl;
        st = clock();
        for (int i = 0; i < 1000000; i++)
        {
            for (int k = 0; k < 10; k++) {
                f1();
            }
        }
        et = clock() - st;
        cout << "f1() : " << et << endl;
        getchar();
        return 0;
}