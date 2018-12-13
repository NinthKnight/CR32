
#include "StdAfx.h"
#include <stdlib.h>
#include <iostream>

template<typename T>
T GetMax(T A)
{
    return A;
}

template<>
int GetMax(int A)
{
    return A;
}

int GetMax(int A)
{
    return A;
}

int main()
{
    std::cout <<GetMax(1.2f) <<std::endl;
    std::cout << GetMax(2) << std::endl;

    //如果有非模板重载会优先进函数 而不是进模板重载
    system("pause");
    return 0;
}

