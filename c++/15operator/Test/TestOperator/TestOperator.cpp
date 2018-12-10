// TestOperator.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <memory>
//运算符重载
/*
  CMystring =运算符重载
  cin / cout  << 
              >>

  //全局运算符重载

  //类运算符重载

  1. 为了某些运算符定义新的功能。
  2. 参数至少有一个类类型。
  3. 运算符重载不改变原有运算符的目数，优先级，尽量保持语义与原有操作符一致。

  ++
  --
  +=
  -=
  []
  <<
  >>

  new 
  delete

  //智能指针
  *
  ->



*/

class CMystring {

public:
    CMystring() {
    
    }

    CMystring(char* psz) {

        strcpy(m_szBuf, psz);
    }

    void append(CMystring& str) {
        strcat(m_szBuf, str.m_szBuf);
    }

    CMystring& operator=(CMystring& obj);
    void operator=(char* psz);

    friend std::ostream& operator<<(std::ostream& cout, CMystring& str);
    //void operator<<(char* psz);

    char& operator[](int nIndex);



private:
    char m_szBuf[256];
};


CMystring operator+(char* psz, CMystring str) {
    
    printf("char* operator+(char* psz, CMystring str)");

    CMystring tmp = psz;
    tmp.append(str);

    return tmp;
}

void operator+(CMystring str, char* psz) {

    printf("operator+(CMystring str, char* psz)");
}

void CMystring::operator=(char* psz) {

    printf("void operator=(CMystring str，char* psz)");
}

CMystring& CMystring::operator=(CMystring& obj) {

    memcpy(m_szBuf, obj.m_szBuf, 256);

    printf("void operator=(CMystring str，char* psz)");

    return *this;
}

char& CMystring::operator[](int nIndex) {

    return m_szBuf[nIndex];
}

std::ostream& operator<<(std::ostream& cout, CMystring& str) {

    cout << str.m_szBuf;

    return cout;
}

class CInt {

public:
    CInt(int n) {
        m_int = n;
    }

    //pre ++
    int operator++() {
        return ++m_int;
    }

    //post ++
    int operator++(int) {
        return m_int++;
    }

    void* operator new(size_t cb){
        void* p = new char[cb];

        return p;
    }

private:
    int m_int;
    int m_nTest;
};

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

class CPointer {
public:
    CPointer(CStudent* pStu) {
        m_pStu = pStu;
    }

    ~CPointer() {
        delete m_pStu;
    }

    CStudent* operator->() {
        return m_pStu;
    }

    CStudent& operator*() {
        return *m_pStu;
    }


private:
    CStudent* m_pStu;

};


int main()
{
    //CStudent* pStu = new CStudent;
    //pStu->foo();

    //CPointer pt(new CStudent);
    //CPointer pt2 = pt;

    //pt->foo();
    //(*pt).foo();

    std::shared_ptr<CStudent> pt(new CStudent);
    std::shared_ptr<CStudent> pt2 = pt;

    pt->foo();
    (*pt).foo();

    //CInt n = 1;
    //CInt* pN = ::new CInt(1);
    

    //CInt n = 1;
    //n++;
    //++n;
    //std::string str1 = " World!";
    //str1[0] = 'b';

    //CMystring str = " World!";
    //char ch = str[0];
    //str[0] = 'a';

    //str << "123";
    //std::cout << " World!" << std::endl;
    //std::cout << str << std::endl;

    //CMystring str1;
    //CMystring str2;
    //str + "Hello";
    //int n, k, j;
    //n = k = j + 1;
    //str2 = str1 = "Hello" + str;
    //int n = 1 + 2;
    //std::string str = "Hello";

    //str = str + " World!";
    //str.append(" World!");


    return 0;
}

