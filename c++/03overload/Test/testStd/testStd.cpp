// testStd.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

//std STL库
using namespace std;
//

//com.tencent.xxx

int cout = 1;

int main()
{
    //输出 cout对象 面向对象语言
    //<< 运算符重载

    
    using std::cout;
    using std::endl;
    //输出Hello World!
    //
    std::cout << "Hello World!" << std::endl;

    int n = 10;

    printf("%d\r\n", n);

    std::cout.setf(std::ios::hex, std::ios::basefield);
    std::cout << n << std::endl;
    std::cout.unsetf(std::ios::hex);
    //std::cout.setf(std::ios::hex, std::ios::basefield);

    std::cout.setf(std::ios::showbase);
    std::cout << 123 << endl;



    //cout << n << endl;

    //::cout = 3;

    return 0;
}

