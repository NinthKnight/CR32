// Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
class CRefCount
{
public:
    CRefCount() {
        m_nUsedCount = 1;
        m_nWeakCount = 1;
    }

    void incUsed() {
        m_nUsedCount++;
    }

    int decUsed() {
        m_nUsedCount--;
        return m_nUsedCount;
    }

    void incWeak() {
        m_nWeakCount++;
    }

    int decWeak() {
        m_nWeakCount--;

        return m_nWeakCount;
    }

    int getUsed() {
        return m_nUsedCount;
    }

private:
    int m_nUsedCount; //强指针引用次数
    int m_nWeakCount; //弱指针引用次数
};

template<typename T>
class CMySmartPtrBase
{
public:
    CMySmartPtrBase() {};
    ~CMySmartPtrBase() {};

    void destroy() {
        delete m_Ptr;
    }

    void release() {
        if (m_pRef != nullptr && m_pRef->decWeak() == 0) {
            delete m_pRef;
        }
    }

protected:
    T* m_Ptr;
    CRefCount* m_pRef;
};

//强指针类型
template<typename T>
class CMyWeakPtr;

template<typename T>
class CStrongPtr : public CMySmartPtrBase<T>
{
    friend class CMyWeakPtr<T>;
public:
    CStrongPtr() {
        m_Ptr = nullptr;
        m_pRef = nullptr;
    }

    explicit CStrongPtr(T* p) {
        m_Ptr = p;
        m_pRef = new CRefCount;
    }

    CStrongPtr(CStrongPtr<T>& obj) {

        m_Ptr = obj.m_Ptr;
        obj.m_pRef->incUsed();
        m_pRef = obj.m_pRef;
    }

    CStrongPtr<T>& operator=(CStrongPtr<T>& obj) {

        if (m_pRef != nullptr && m_pRef->decUsed() == 0) {
            destroy();
            release();
        }

        m_Ptr = obj.m_Ptr;
        obj.m_pRef->incUsed();
        m_pRef = obj.m_pRef;

        return *this;
    }

    CStrongPtr(CMyWeakPtr<T>& obj) {
        m_Ptr = obj.m_Ptr;
        obj.m_pRef->incUsed();
        m_pRef = obj.m_pRef;
    }

    ~CStrongPtr() {
        if (m_pRef != nullptr && m_pRef->decUsed() == 0) {
            destroy();
            release();
        }
    }

    T& operator*() {
        return *m_Ptr;
    }

    T* operator->() {
        return m_Ptr;
    }

    T* get() {
        return m_Ptr;
    }
};


//强指针类型
template<typename T>
class CMyWeakPtr : public CMySmartPtrBase<T>
{
public:
    friend class CStrongPtr<T>;

    CMyWeakPtr() {
        m_Ptr = nullptr;
        m_pRef = nullptr;
    }

    CMyWeakPtr(CStrongPtr<T>& obj) {
        //release();

        m_Ptr = obj.m_Ptr;
        obj.m_pRef->incWeak();
        m_pRef = obj.m_pRef;
    }

    CMyWeakPtr<T>& operator = (CStrongPtr<T>& obj) {
        release();

        m_Ptr = obj.m_Ptr;
        obj.m_pRef->incWeak();
        m_pRef = obj.m_pRef;

        return *this;
    }

    CMyWeakPtr(CMyWeakPtr<T>& obj) {

        m_Ptr = obj.m_Ptr;
        obj.m_pRef->incWeak();
        m_pRef = obj.m_pRef;
    }

    ~CMyWeakPtr() {
        release();
    }

    CStrongPtr<T>& lock() {
        if (m_pRef == nullptr) {
            return CStrongPtr<T>();
        }

        return CStrongPtr<T>(*this);
    }

    bool IsExpried() {
        if (m_pRef == nullptr) {
            return true;
        }

        return m_pRef->getUsed() == 0;
    }
};

class CSon;

class CTest {
public:

    ~CTest() {
        printf("~CTest()\r\n");
    }

    void set(CStrongPtr<CSon> p2) {
        m_p1 = p2;
    }

    CStrongPtr<CSon> m_p1;
};

class CSon {
public:

    ~CSon() {
        printf("~CSon()\r\n");
    }

    void set(CStrongPtr<CTest> p2) {
        m_p1 = p2;
    }

    CMyWeakPtr<CTest> m_p1;
};

void foo() {
    CTest* father = new CTest();
    CSon* son = new CSon();


    CStrongPtr<CTest> ptrFather(father);
    CStrongPtr<CSon> ptrSon(son);

    father->set(ptrSon);
    son->set(ptrFather);

}

int _tmain(int argc, _TCHAR* argv[])
{
    foo();

    return 0;
}

