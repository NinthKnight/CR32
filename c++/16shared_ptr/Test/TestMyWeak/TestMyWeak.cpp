// TestMyWeak.cpp : 定义控制台应用程序的入口点。
//

// TestSharedPtr.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"




//模板
template<typename T>
class CRefCount {
public:
    CRefCount(T* pStu) {
        m_pStu = pStu;
        m_nCount = 1;
    }

    int AddRef() {
        return ++m_nCount;
    }

    int DelRef() {
        if (--m_nCount == 0) {
            delete m_pStu;
            return 0;
        }
        return m_nCount;
    }

private:
    T* m_pStu;
    int m_nCount;
};

template<typename T>
class CSharedPtr {
public:
    explicit CSharedPtr() {
        m_pStu = nullptr;
        m_pRefCount = nullptr;
    }

    explicit CSharedPtr(T* pStu) {
        m_pStu = pStu;
        m_pRefCount = new CRefCount<T>(pStu);
    }

    CSharedPtr(CSharedPtr& obj) {
        m_pStu = obj.m_pStu;

        m_pRefCount = obj.m_pRefCount;
        if (m_pRefCount != NULL){
            m_pRefCount->AddRef();
        }
        
    }

    CSharedPtr& operator=(CSharedPtr& obj) {

        if (&obj == this) {
            return *this;
        }

        if (m_pRefCount != NULL && m_pRefCount->DelRef() == 0) {
            delete m_pRefCount;
            m_pRefCount = NULL;
        }
        

        m_pStu = obj.m_pStu;
        m_pRefCount = obj.m_pRefCount;
        if (m_pRefCount != NULL) {
            m_pRefCount->AddRef();
        }
        

    }


    ~CSharedPtr() {
        if (m_pRefCount != NULL && m_pRefCount->DelRef() == 0) {
            delete m_pRefCount;
            m_pRefCount = NULL;
        }
        

    }

    T* operator->() {
        return m_pStu;
    }

    T& operator*() {
        return *m_pStu;
    }


private:
    T* m_pStu;
    CRefCount<T>* m_pRefCount;
};

class CSon;
class CFather {
public:
    CFather() {
        //m_pSon = nullptr;
    }

    void Set(CSharedPtr<CSon> pSon) {
        m_pSon = pSon;
    }

    ~CFather() {
        //if (m_pSon != nullptr) {
        //    delete m_pSon; 
        //}
        printf("~CFather()\r\n");
    }

private:
    CSharedPtr<CSon> m_pSon;
};

class CSon {
public:
    CSon() {
    }

    ~CSon() {
        printf("~CSon()\r\n");
    }

    void Set(CSharedPtr<CFather> pFather) {
        m_pFather = pFather;
    }

private:
    CSharedPtr<CFather> m_pFather;
};



int main()
{
    CFather* pFather = new CFather;
    CSon* pSon = new CSon;

    CSharedPtr<CFather> father(pFather);
    CSharedPtr<CSon> son(pSon);

    father->Set(son);
    son->Set(father);

   return 0;
}



