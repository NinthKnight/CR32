// testStd.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>

//std STL��
using namespace std;
//

//com.tencent.xxx

int cout = 1;

int main()
{
    //��� cout���� �����������
    //<< ���������

    
    using std::cout;
    using std::endl;
    //���Hello World!
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

