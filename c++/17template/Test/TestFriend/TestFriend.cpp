// TestFriend.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

template<typename T>
class CFriend;

class CTest {

    template<typename T>
    friend class CFriend;

    template<typename T>
    friend T GetMax(T a, T b);
public:


private:
    int m_nTest;
};

template<typename T>
T GetMax(T a, T b) {
    CTest t;
    t.m_nTest = 1;
    return a;
}

template<typename T>
class CFriend {

public:
    void foo() {
        CTest t;
        t.m_nTest = 1;
    }

private:
    T m_nFriend;
};


int main()
{
    CFriend<int> f;

    f.foo();
    
    //GetMax(1, 2);

    return 0;
}

