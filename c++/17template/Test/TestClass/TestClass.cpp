// TestClass.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

//类模板

template<typename T, int SIZE = 101, int SIZE2 = 102>
class CTest {
public:
    CTest(T n) {
        m_nTest = n;
    }

private:
    T m_nTest;
    int m_nAry[SIZE];
};


int main()
{
    //产生模板实例
    //类模板必须显式实例化
    int n = 100;
    CTest<int> t(1);


    return 0;
}

