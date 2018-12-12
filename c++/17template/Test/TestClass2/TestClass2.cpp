// TestClass2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

template<typename T>
class CTest {
public:
    CTest(T n) {
        m_nTest = n;
    }

    void foo(T n);

private:
    T m_nTest;

    //静态数据成员
    static T m_nStatic;
};

template<typename T>
T CTest<T>::m_nStatic;


//类模板函数
template<typename T>
void CTest<T>::foo(T n) {
    m_nTest = n;
    m_nStatic = 1;
}

//类模板函数特例
//template<>
//void CTest<char*>::foo(char* n) {
//    m_nTest = n;
//}

//类模板特例
//template<>
//class CTest<char*> {
//public:
//    CTest(char* n) {
//        m_nTest = n;
//    }
//
//    void foo(char* n) {
//        m_nTest = n;
//    }
//
//private:
//    char* m_nTest;
//};



int main()
{


    CTest<int> t(1);
    t.foo(123);
    //
    //char* p = "123";
    //CTest<char*> t2(p);
    //t2.foo(p);


    return 0;
}

