/*
编写一个持有单一类型参数（T)的函数模板，
它接受了4个函数参数：
一个T类数组，
一个开始索引值，
指出下面的代码为什么无法编译？
*/

#include "StdAfx.h"
#include <stdlib.h>
#include <iostream>

template<class T> 
double pythag(T a, T b, T c) 
{
    return (-b + sqrt(double(b*b - 4 * a*c))) / 2 * a;
}

int main()
{
    pythag(1, 2, 3);
    pythag(1.0, 2.0, 3.0);
    //pythag(1, 2.0, 3.0);
    pythag<double>(1, 2.0, 3.0);

    /*
        不过是第三行的问题
        因为第三行存在二义性
        编译器不知道是使用int 还是double
        第四行显示特化为double 所以还可以使用
    */
    system("pause");
    return 0;
}


