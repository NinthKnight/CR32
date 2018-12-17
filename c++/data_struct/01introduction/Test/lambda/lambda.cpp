// lambda.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

//lambda表达式 -- 匿名函数
//表达式:
//[capture](paras)mutable->return type{statement}
/*
[捕获列表](参数列表) mutable(可选) 异常属性 -> 返回类型 {
// 函数体
}

    int foo(int n1, int n2){
    
    }

    ==》

    [](int n1, int n2)->int{

    }

*/

void foo() {

    int n = 2;
    int m = 3;
    
    //&
    int k = [&](int n1, int n2)mutable->int {

        n++;
        printf("n = %d\r\n", n);
        printf("m = %d\r\n", m);
        return n1 + n2;
    }(1, 2);

    printf("n = %d\r\n", n);
    //printf("k = %d\r\n", k);

    //auto f = [](int n1, int n2)->int {

    //};
    //f(1, 2);


}

int main()
{
    foo();
    return 0;
}

