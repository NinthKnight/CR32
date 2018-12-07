// TestRefCount.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
//���ü���


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
            delete  this; //������ɱ
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

    //��������
    //CStudent(CStudent& obj) = delete;
    CStudent(CStudent& obj) {

        std::cout << "CStudent(CStudent& obj)" << std::endl;

        m_nGender = obj.m_nGender;
        m_pRef = obj.m_pRef;
        obj.m_pRef->Add();


        //m_nName = new char[strlen(obj.m_nName) + 1];
        //strcpy_s(m_nName, strlen(obj.m_nName) + 1, obj.m_nName);
    }

    //=���������
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

    //��̬��Ա����,û��thisָ��ģ�ֻ�ܷ��ʾ�̬���ݳ�Ա
    static void foo() {
        printf("static void foo()");

        //m_nCount = 1;
    }

public:
    //int* m_pCount; //��̬���ݳ�Ա

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


    //CStudent stu3("����");

    //stu1 = stu3;




    //stu1.m_nCount = 1;
    //stu2.m_nCount = 2;
    //printf("%d %d", CStudent::m_nCount, stu2.m_nCount);

    return 0;
}

