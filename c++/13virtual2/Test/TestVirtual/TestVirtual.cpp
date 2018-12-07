// TestVirtual.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

class CPerson{
public:

    virtual void foo() {
        printf("void CPerson::foo()");
    }

    void foo(int n) {
        printf("void CPerson::foo(int n)");
    }

    virtual void foo(char* p) {
        printf("void CPerson::foo(char* p)");
    }

    virtual void foo(float f) {
        printf("void CPerson::foo(float f)");
    }

};

class CChinese : public CPerson{
public:

    virtual void foo() {
        printf("void CChinese::foo()");
    }

    virtual void foo(int n) {
        printf("void CChinese::foo(int n)");
    }

    void foo(float f) {
        printf("void CChinese::foo(float f)");
    }

    virtual void foo(char* p) {
        printf("void CChinese::foo(char* p)");
    }

};

/*
    调用者的类型来决定查找的起点
       (1) 在调用者的类中，查找同名函数：
          1）如果没有，则往上一层查找，如果均找不到，则报错（未定义）
          2）如果有，则不会往上面查找，可见的域就是当前找到的同名函数所在的域（函数隐藏）
          
      （2）在当前可见的域中，找到最佳函数。（函数重载规则）
          1） 如果唯一的最佳函数不是虚函数，那么该调用是直接调用。
          2） 如果唯一的最佳函数是虚函数,判断调用者是否是指针或引用
               1.1) 调用者是指针或引用，则是间接调用（函数覆盖规则）
               1.2）调用者不是指针或引用，则是直接调用
             
       直接调用: 谁的类型调谁
       间接调用：谁的虚表调谁

*/

int main()
{
    CPerson per;
    CChinese chs;

    CPerson* pPer = &per;
    CPerson* pPer2 = &chs;
    CPerson& perRef = chs;

    CChinese* pChs = &chs;

    per.foo("Hello");
    pPer->foo("Hello");
    pPer2->foo("Hello");
   

    pPer->foo();
    pPer2->foo();
    perRef.foo();

    pPer->foo(2);
    pChs->foo(2);
    pPer2->foo(2);
    perRef.foo(2);

    pPer->foo(2.0f);
    pPer2->foo(2.0f);
    perRef.foo(2.0f);

   
    return 0;
}

