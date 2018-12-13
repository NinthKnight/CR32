/*
研究stl中的iostream，说明cout,endl,<<,hex分别是什么含义，解释下面的代码：
```
cout << "hello World" <<  hex << 123 << endl;
```
*/

#include "StdAfx.h"
#include <stdlib.h>
#include <iostream>

class CMyCout
{
public:
    CMyCout()
    {
        m_Type = NUM_DEC;
    }
    enum NUM_TYPE
    {
        NUM_DEC,
        NUM_HEX
    };

    CMyCout& operator << (char* szStr);
    CMyCout& operator << (int nNum);
    CMyCout& operator << (CMyCout& (*foo)(CMyCout&));
    friend CMyCout& hex(CMyCout& obj);
private:
    NUM_TYPE m_Type;
};

CMyCout& hex(CMyCout& obj)
{
    obj.m_Type = obj.NUM_HEX;
    return obj;
}

CMyCout& endl(CMyCout & obj)
{
    puts("\n");
    return obj;
}

int main(void)
{
    CMyCout MyCout;

    std::cout << "hello World" << std::hex << 123 << std::endl;
    //实际上 cout是一个对象 << 是重载运算符

    //手动实现一个简单版本
    MyCout << "hello World" << hex << 123 << endl;

    system("pause");
    return 0;
}

CMyCout & CMyCout::operator<<(char * szStr)
{
    printf("%s", szStr);
    return *this;
}

CMyCout & CMyCout::operator<<(int nNum)
{
    if (NUM_DEC == m_Type)
    {
        printf("%d", nNum);
    }
    else if (NUM_HEX == m_Type)
    {
        printf("%x", nNum);
    }
    return *this;
}

CMyCout & CMyCout::operator<<(CMyCout &(*foo)(CMyCout &))
{
    (*foo)(*(CMyCout *)this);
    return *this;
}





