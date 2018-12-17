// cast.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

//cast 转换
//1. const_cast
//   用于去除或者添加上const属性或volatility

//2. static_cast
//   (1) 等价于C中的隐式转换
//   (2) 没有运行时类型检查来保证转换的安全性

//3. dynamic_cast
//   (1) 派生类与基类直接的转换
//   (2) 基类必须要有虚函数
//  （3）提供运行时类型检查

//4. reinterpret_cast
//   等价于强转 


class CFather {
public:
    virtual void test() {
    }
};

class CSon : public CFather{
public:

};

void foo_dynamic() {
    CFather fa;
    CSon son;

    CFather* pFather = dynamic_cast<CFather*>(&son);
    CSon* pSon = dynamic_cast<CSon*>(&fa);
    CSon* pSon2 = dynamic_cast<CSon*>(pFather);
    CSon* pSon3 = static_cast<CSon*>(&fa);
    


}


void foo_static() {
    int n = 1;
    float f = (float)n;



    //float f2 = static_cast<float>(n);
    ////int f3 = static_cast<int>(&n);
    //int f4 = reinterpret_cast<int>(&n);
    //int f5 = (int)(&n);
    //float f6 = f4;


}

int main()
{
    foo_dynamic();

    //volatile int n;
    return 0;
}

