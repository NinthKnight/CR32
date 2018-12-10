// TestFriend.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

//友元 friend


class CTest {
public:
    void foo();
};

class CTest2 {
public:
    void foo();

};

class CStudent {
    //友元全局函数
    friend void foo();

    //友元成员函数
    friend void CTest::foo();

    //友元类
    friend class CTest2;

public:
    
    CStudent() {
    
    }

private:
    int m_nGender;
};

void foo() {
    CStudent stu;

    stu.m_nGender = 1;
}

void CTest::foo() {
    CStudent stu;
    stu.m_nGender = 1;
}

void CTest2::foo() {
    CStudent stu;
    stu.m_nGender = 1;
}

int main()
{
    CTest2 t;
    t.foo();

    return 0;
}

