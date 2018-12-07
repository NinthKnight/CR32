// TestRefCount.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
//引用计数


class CRefCount {
public:
    CRefCount(char* pszName) {
        m_nCount = 1;
        
        char* pBuf = new char[strlen(pszName) + 1];
        strcpy_s(pBuf, strlen(pszName) + 1, pszName);
        m_pName = pBuf;
    }

    ~CRefCount() {
        if (m_pName != nullptr) {
            delete [] m_pName;
        }
    }

    void Add() {
        m_nCount++;
    }

    void Dec() {
        if (--m_nCount == 0) {
            delete  this; //对象自杀
        }
    }


private:
    int m_nCount;
    char* m_pName;
};


class CStudent {
public:
    CStudent(char* pName, int nGender = 1)
        :m_nGender(nGender)
    {
        m_pRef = new CRefCount(pName);

        std::cout << "CStudent(int nGender)" << std::endl;
    }

    //拷贝构造
    //CStudent(CStudent& obj) = delete;
    CStudent(CStudent& obj) {

        std::cout << "CStudent(CStudent& obj)" << std::endl;

        m_nGender = obj.m_nGender;
        m_pRef = obj.m_pRef;
        obj.m_pRef->Add();


        //m_nName = new char[strlen(obj.m_nName) + 1];
        //strcpy_s(m_nName, strlen(obj.m_nName) + 1, obj.m_nName);
    }

    //=运算符重载
    CStudent& operator=(CStudent& obj) {
        std::cout << "CStudent& operator=(CStudent& obj)" << std::endl;

        if (this == &obj) {
            return *this;
        }

        m_pRef->Dec();

        m_pRef = obj.m_pRef;
        obj.m_pRef->Add();


        m_nGender = obj.m_nGender;

        //m_nName = new char[strlen(obj.m_nName) + 1];
        //strcpy_s(m_nName, strlen(obj.m_nName) + 1, obj.m_nName);

        return *this;
    }


    ~CStudent()
    {
        std::cout << "~CStudent()" << std::endl;

        m_pRef->Dec();

        //if (--m_nCount == 0 && m_nName != NULL) {
        //    delete[] m_nName;
        //    m_nName = NULL;
        //}

    }

    //静态成员函数,没有this指针的，只能访问静态数据成员
    static void foo() {
        printf("static void foo()");

        //m_nCount = 1;
    }

public:
    //int* m_pCount; //静态数据成员

private:
    int m_nGender;
    
    CRefCount* m_pRef;
    //char* m_nName;
};

//int CStudent::m_nCount;

int main()
{

    //CStudent::foo();
    CStudent* pStu1 = new CStudent("Hello");




    CStudent stu2 = *pStu1;

    delete pStu1;


    //CStudent stu3("张三");

    //stu1 = stu3;




    //stu1.m_nCount = 1;
    //stu2.m_nCount = 2;
    //printf("%d %d", CStudent::m_nCount, stu2.m_nCount);

    return 0;
}

