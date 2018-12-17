// RightRef.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <memory>

//引用
//右值引用
//   1.常量，常量表达式
//   2.将亡值

class CTest {
public:
    CTest() {
        printf("CTest()\r\n");
    }

    CTest(CTest& obj) {
        printf("CTest(&obj)\r\n");
        //深拷贝
        //memcpy(m_pBuf, obj.m_pBuf, nLength);



    }

    //移动构造
    CTest(CTest&& obj) {
        printf("CTest(&&obj)\r\n");

        //"偷"资源
        m_pBuf = obj.m_pBuf;
        obj.m_pBuf = nullptr;


    }

    

    ~CTest() {
        printf("~CTest()\r\n");
    }

private:
    char* m_pBuf;

};

CTest foo() {
    CTest t;

    return t;
}

void foo2(CTest&& t) {


}


int main()
{
    CTest t;

    foo2(std::move(t));
    foo2((CTest&&)t);

    //CTest t1 = foo();


    //int n;
    //n = 1;

    //左值引用
    //int& ref = n;
    //ref = 1123;

    ////右值引用
    //int&& ref2 = 1;
    //ref2 = 3;

    return 0;
}

