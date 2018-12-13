/*
    使用运算符重载实现变体，支持int float char*等类型。
*/

#include "StdAfx.h"
#include <stdlib.h>
#include <iostream>

template<typename T>
T GetSum(T A, T B)
{
    return A + B;
}

template<>
char* GetSum(char* A, char* B)
{
    strcat(A, B);
    return A;
}

/*------------------函数模板特化-----------------*/

template<typename T>
class TestClass
{
public:
    TestClass()
    {
        m_T = 233;
    }

    void MyPrint()
    {
        std::cout << m_T << std::endl;
    }

private:
    T m_T;
};

template<>
class TestClass<char*>
{
public:
    TestClass()
    {
        m_T = "Hello";
    }
    void MyPrint()
    {
        std::cout << m_T << std::endl;
    }

private:
    char* m_T;
};

/*------------------类模板特化-----------------*/

template<typename T>
class TestClass2 
{
public:
    TestClass2()
    {
        m_T = 1.1;
    }

    void MyPrint()
    {
        std::cout << m_T << std::endl;
    }

private:
    static T m_T;
};

template<typename T>
T TestClass2<T>::m_T;


int main()
{
    char szA[16]  = "Hello";
    char szB[] = " World!";
    std::cout << GetSum(5, 6) << std::endl;
    std::cout << GetSum(szA, szB) << std::endl;
    /*------------------函数模板特化-----------------*/

    TestClass<int> Test1;
    Test1.MyPrint();
    TestClass<char*> Test2;
    Test2.MyPrint();
    /*------------------类模板特化-----------------*/
    /*---------------类模板必须显示声明-----------------*/

    TestClass2<double> Test3;
    Test3.MyPrint();
    /*------------------静态成员数据特化-----------------*/
    system("pause");
    return 0;
}


