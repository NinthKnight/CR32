// homework.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include "TestA.h"
#include "TestB.h"

//��ǰ����
//class CTestA;
//
//class CTestB
//{
//public:
//    void foo(CTestA* pTestA) {
//        std::cout << "class CTestB:foo" << std::endl;
//        //pTestA->foo();
//    }
//
//    CTestA* A;
//
//};
//
//
//class CTestA
//{
//public:
//    void foo(CTestB* pTestB) {
//        std::cout << "class CTestA:foo" << std::endl;
//        //CTestB* p = pTestB;
//        //p->foo();
//    }
//
//};




int main()
{
    int n = 0;
    int* p = &n;
    printf("p = %p\r\n", p);

    CTestA testA;
    CTestB testB;

    //testA.foo(&testB);
    testB.foo(&testA);

    return 0;
}

