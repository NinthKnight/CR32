// TestInherit.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

//类模板继承
template <typename T>
class CFather {
public:

private:
    T m_nTest;
};

template <typename T>
class CSon : public CFather<T>{
public:
    CSon() {
        m_nSon = 1;
    }
private:
    T m_nSon;
};

//类模板继承特例
template <>
class CSon<char*> : public CFather<char*> {
public:
    CSon() {
        m_nSon = "123";
    }
private:
    char* m_nSon;
};

int main()
{
    CSon<char*> son;

    return 0;
}

