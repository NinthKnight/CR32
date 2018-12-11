// TestSharedPtr.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


//简单版本的智能指针
//智能指针是什么？
//1. 智能指针本质是对象，但是使用起来像指针。
//2. 像指针：重载了->和*
//为什么需要使用智能指针？
//  堆空间通常需要手动释放，将堆的指针放入到智能指针中
//利用智能指针对象自动析构的特点，从而自动释放堆空间。

class CStudent {
public:
    CStudent() {

    }

    ~CStudent() {
        printf("~CStudent()");
    }

    void foo() {
        printf("CStudent\r\n");
    }

private:
    int m_nGender;
};

class CRefCount {
public:
    CRefCount(CStudent* pStu) {
        m_pStu = pStu;
        m_nCount = 1;
    }

    void AddRef() {
        m_nCount++;
    }

    void DelRef() {
        if (--m_nCount == 0) {
            delete m_pStu;
            delete this;
        }
    }

private:
    CStudent* m_pStu;
    int m_nCount;
};

class CSharedPtr {
public:
    explicit CSharedPtr(CStudent* pStu) {
        m_pStu = pStu;
        m_pRefCount = new CRefCount(pStu);
    }

    CSharedPtr(CSharedPtr& obj) {
        m_pStu = obj.m_pStu;

        m_pRefCount = obj.m_pRefCount;
        m_pRefCount->AddRef();
    }

    CSharedPtr& operator=(CSharedPtr& obj) {
    
        if (&obj == this) {
            return *this;
        }

        m_pRefCount->DelRef();

        m_pStu = obj.m_pStu;
        m_pRefCount = obj.m_pRefCount;
        m_pRefCount->AddRef();

    }


    ~CSharedPtr() {
        m_pRefCount->DelRef();
        
    }

    CStudent* operator->() {
        return m_pStu;
    }

    CStudent& operator*() {
        return *m_pStu;
    }


private:
    CStudent* m_pStu;
    CRefCount* m_pRefCount;
};


int main()
{
    CStudent* pStu1 = new CStudent;
    CSharedPtr p(pStu1);
    CSharedPtr p2 = p;

    CStudent* pStu2 = new CStudent;
    CSharedPtr p3(pStu2);
    p2 = p2;
    p2 = p3;

    return 0;
}

