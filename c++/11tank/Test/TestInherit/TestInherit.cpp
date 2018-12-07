// TestInherit.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <iostream>

//面向对象：继承
//
namespace CR32{
    void foo() {
        printf("CR32: void foo()\r\n");
    }
}

void foo() {
    printf("global: void foo()\r\n");
}

float n = 3;

class CPerson {
public:
    CPerson(){
        n = 3;
    }

    void foo(char* p) {
        printf("void CPerson::foo(char* p)\r\n");
    }

    int n;
};

class CTeacher: public CPerson {
public:
    CTeacher(): CPerson()
    {
    }

    void foo(int n) {
        printf("void CTeacher::foo(int n)\r\n");
    }

    void test() {
        //foo();
        CPerson::n = 1;
        ::n = 3.0f;
    }

    char* n;
private:
};

/*
    数据隐藏：
        （1） 同名，
        （2） 作用域不同
         (3)  类型不考虑
 
    函数隐藏：
         (1) 同名
        （2) 参数，返回值，调用约定都不考虑
        （3）作用域不同

        从内向外查找，一旦找到同名函数，则外部函数被隐藏。 内部再经过函数重载的规则匹配。
*/
int main()
{
    CTeacher t;
    //t.foo();
    t.test();
    

    return 0;
}

