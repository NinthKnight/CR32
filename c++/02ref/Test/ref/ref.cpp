// ref.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

//左值引用
//1. 编译器产生的关联对应的存储器地址常量指针
//2. 引用一旦初始化后，不能改变引用的关系
//3. 引用必须赋初值,不能为NULL或常量,应该是一个变量
//4. 常量引用可以用常量初始化
//5. 使用场合

//int* foo() {
//    int n = 1;
//    return &n;
//}

//int foo2(int* p) {
//    char szBuf[256] = { 0 };
//    *p = 123;
//
//}

void exchange(int*& n1, int*& n2) {
    int* k = n1;
    n1 = n2;
    n2 = k;
    return;
}

int& foo_ref() {
    int n = 1;
    return n;
}

int main()
{
    int m = 1;
    int n = 2;

    int* pM = &m;
    int* pN = &n;

    exchange(pM, pN);

    //int& nRef = foo_ref();
    //
    //nRef = 3;

    //foo2(pN);


    return 0;


    //int n = 0;
    //int m = 2;
    ////int* pN = &n;
    ////*pN = 1;
    //const int& refN = 1000; //引用
    

                      
    //refN = m;
    //refN = 1;


    return 0;
}

