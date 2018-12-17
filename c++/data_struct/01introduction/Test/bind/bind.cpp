// bind.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <functional>

class Functor {
public:
    int operator()(int n) {
        m_n = n;
        return n;
    }

    int test(int n) {
        m_n = n;
        return m_n;
    }

    int m_n;
};


// 按照顺序输出x, y, x
void print_func(int x, int y, int z)
{
    std::cout << x << " " << y << " " << z << std::endl;
}
std::function<void(int, int, int)> Func;

int main()
{
    Functor obj;
    //std::function<int(Functor*)> f4 = &Functor::test;
    //f4(&obj);

    std::function<int(int)> f5 = std::bind(&Functor::test, &obj, std::placeholders::_1);
    f5(1);



    std::function<void()> f = std::bind(&print_func, 1, 2, 3);
    f(); // 输出： 1 2 3

    std::function<void(int)> f2 = std::bind(&print_func, 1, std::placeholders::_1, 3);
    f2(5); // 输出： 1 5 3


    std::function<void(int,int)> f3 = std::bind(&print_func, std::placeholders::_2, std::placeholders::_1, 3);
    f3(5, 1); // 输出： 1 5 3

    Func = std::bind(&print_func, std::placeholders::_2, std::placeholders::_1, 3);
    Func(1, 2, 7); // 输出： 2 1 3

    int n = 10;
    Func = std::bind(&print_func, std::placeholders::_1, std::placeholders::_1, n);
    Func(5, 6, 7); // 输出： 5 5 10

    getchar();
    return 0;
}

