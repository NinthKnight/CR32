// Copy.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

//拷贝构造
// 1. 功能：将一个对象的内容拷贝给另一个对象，本质也是构造函数。
// 2. 系统会提供一个默认的拷贝构造函数，默认构造是一种浅拷贝（只拷贝值）
//    可以使用=delete禁用.
// 3. 浅拷贝：CStuent stu2 = stu1等价于memcpy（&stu2, &stu1, sizeof(stu1)）。
// 4. 深拷贝：自己实现，会对资源重新申请，从而避免了析构中重复释放资源的问题。

// =运算符的赋值
// 1. 系统会提供一个默认的=运算符的赋值的函数， “=”运算符重载,也是浅拷贝。

//为了避免浅拷贝带来的资源重复释放的问题，重写拷贝构造和=运算符的运算符重载，或者禁用。

class CStudent {
public:
    CStudent(char* pName,int nGender = 1)
        :m_nGender(nGender)
    {     
        m_nName  = new char[strlen(pName) + 1];
        strcpy_s(m_nName, strlen(pName) + 1, pName);

        std::cout << "CStudent(int nGender)" << std::endl;
    }

    //拷贝构造
    //CStudent(CStudent& obj) = delete;
    CStudent(CStudent& obj) {

        std::cout << "CStudent(CStudent& obj)" << std::endl;

        m_nGender = obj.m_nGender;
        
        m_nName = new char[strlen(obj.m_nName) + 1];
        strcpy_s(m_nName, strlen(obj.m_nName) + 1, obj.m_nName);
    }

    //=运算符重载
    CStudent& operator=(CStudent& obj) {
        std::cout << "CStudent& operator=(CStudent& obj)" << std::endl;

        if (m_nName == obj.m_nName) {
            return *this;
        }

        if (m_nName != NULL) {
            delete [] m_nName;
            m_nName = NULL;
        }

        m_nGender = obj.m_nGender;

        m_nName = new char[strlen(obj.m_nName) + 1];
        strcpy_s(m_nName, strlen(obj.m_nName) + 1, obj.m_nName);

        return *this;
    }


    ~CStudent()
    {
        std::cout << "~CStudent()" << std::endl;
        if (m_nName != NULL) {
            delete[] m_nName;
            m_nName = NULL;
        }
        
    }

private:
    int m_nGender;
    char* m_nName;
};



int main()
{
    char szName[] = "zhangsan";
    CStudent stu1(szName, 1);

    //CStudent stu1 = 1;
    CStudent stu2("1");
    stu2 = stu1;

   
    CStudent stu3 = stu2;
    CStudent stu4 = stu2;
    CStudent stu5 = stu2;
    CStudent stu6 = stu2;


    //int n = 1;
    //printf("n=%d\r\n",n = 2);


    return 0;
}

