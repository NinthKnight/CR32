/*
编写一个持有单一类型参数（T)的函数模板，
它接受了4个函数参数：
一个T类数组，
一个开始索引值，
一个结束索引值（在允许范围之内的）
一个可选择的初始值。
函数返回指定范围内所有数组元素值和初始值的和。
用默认构造函数为T类型的数据用默认方式赋初值。
*/

#include "StdAfx.h"
#include <stdlib.h>
#include <iostream>

template<typename T>
T GetSum(T* A, int nBegin , int nEnd, int nStart = 0)
{
    T nReulut = 0;
    for (int i = nStart; i < nEnd; i++)
    {
        nReulut += A[i];
    }
    return nReulut;
}

template<>
double GetSum(double* A, int nBegin, int nEnd, int nStart)
{
    double nReulut = 0;
    for (int i = nStart; i < nEnd; i++)
    {
        nReulut += A[i];
    }
    return nReulut;
}

template<>
int GetSum(int* A, int nBegin, int nEnd, int nStart)
{
    int nReulut = 0;
    for (int i = nStart; i < nEnd; i++)
    {
        nReulut += A[i];
    }
    return nReulut;
}

int main()
{
    int arynTemp[10] = { 1,2,3,4,5,6,7,8,9,10 };
    double arydblTemp[3] = { 1.1,2.7,3.6 };

    int nResult = GetSum(arynTemp, 0, 5);
    std::cout << nResult << std::endl;

    double dblResult = GetSum(arydblTemp, 0, 3);
    std::cout << dblResult << std::endl;

    nResult = GetSum<int>(arynTemp, 0, 8 ,0);
    std::cout << nResult << std::endl;

    dblResult = GetSum<double>(arydblTemp, 0, 2, 0);
    std::cout << dblResult << std::endl;
    //显示特例化不可以用默认参
    system("pause");
    return 0;
}

