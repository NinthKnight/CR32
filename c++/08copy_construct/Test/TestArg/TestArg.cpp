// TestArg.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

class CTest {
public:
    CTest(int n = 1) 
        :m_nTest(n)
    {
        printf("CTest()\r\n");
    }

    CTest(CTest& obj)
    {
        printf("CTest(CTest& obj)\r\n");
        m_nTest = obj.m_nTest;
    }

    CTest operator=(CTest& obj) {
        printf("operator=(CTest& obj)\r\n");
        m_nTest = obj.m_nTest;
        return *this;
    }

    ~CTest() {
        printf("~CTest()\r\n");
    }

    //常成员函数
    void foo_test()  const {
        //m_nTest = 1;
        //this->m_nTest = 1;
        CTest* p = const_cast<CTest*>(this);
        p->m_nTest = 1;
        //this = &m_nTest;
        //m_n_mutable_Test = 2;
        printf("m_nTest = %d\r\n", m_nTest);
    }

    void foo_test1(){
        //m_nTest = 1;
        //this->m_nTest = 1;
      
        //this = &m_nTest;
        //m_n_mutable_Test = 2;
        printf("m_nTest = %d\r\n", m_nTest);
    }

private: 
    mutable int m_n_mutable_Test;
    int m_nTest;
};

//const 常成员函数：
// 1. 该函数内部不能修改类的成员变量(除了mutable修饰以外的成员变量)
// 2. 原因是因为常成员函数中的this指针的类型是const T* const;
// 3. 普通的成员函数的this指针的类型是T* const;


//对象作为参数
//1. 形参会拷贝构造产生: void foo_arg(CTest tArg)
//2. 通常参数的传递会使用引用(const 引用)： void foo_argRef(const CTest& tRefArg)，

void foo_arg(CTest tArg) {
    tArg.foo_test();
}

void foo_argRef(const CTest& tRefArg) {
    tRefArg.foo_test();
}

void foo(int nArg) {
    nArg = 2;
}

//对象作为返回值，也会有拷贝构造
// 1. 如果外部没有接受函数的对象，该返回的对象是个无名对象，当遇到该行的“;”时，析构。
//    foo_rtn().foo_test() , printf("123\r\n");printf("456\r\n");
//    123
//    ~CTest() -->说明遇到；析构
//    456
    


CTest foo_rtn() {
    //CTest t(1);

    return 1;
}

//无名对象
// CTest(1);
int main()
{
    //foo_rtn().foo_test() , printf("123\r\n");
    //printf("456\r\n");
    CTest t = foo_rtn();

    //int n = 1;
    //foo(n);

    //CTest t = 1;

    //CTest t;
    //foo_arg(1);
    //foo_arg(CTest(1));
    
    //foo_argRef(t);

    return 0;
}

