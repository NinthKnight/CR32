/*
    定义一个持有单一类型参数的类模板，将其命名为Bob。
    使Bob成为一个名为Friendly的模板类的所有实例的友元，
    并且成为一个名为Picky的类模板的友元——仅当Bob和Picky的类型参数完全相同的时候。
    提供一些能证明这些类的友元关系的Bob成员函数。
*/

#include "StdAfx.h"
#include <stdlib.h>
#include <iostream>

template<typename T>
class CBob
{
public:
};

template<typename T>
class CFriendly
{
    CFriendly()
    {
        m_nNum = 0;
    }
public:
    friend CBob;
private:
    int m_nNum;
};

template<typename T>
class CPicky
{
public:
};

int main(void)
{

    system("pause");
    return 0;
}







