// TestContruct.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

class CTest {
public:
    CTest() {
        //
        printf("CTest() before\r\n");
        //throw 1;
        printf("CTest() after\r\n");
    }

    ~CTest() {
        //
        printf("~CTest() before\r\n");
        //throw(1);
        printf("~CTest() after\r\n");
        
    }


};

int main()
{
    try {
            CTest t;
            throw 1;
    }
    catch (...) {
        printf("catch (...)");
    }


    return 0;
}

