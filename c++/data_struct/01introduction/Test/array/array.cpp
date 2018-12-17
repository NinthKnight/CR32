// array.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

//存储一些字符
//"Hello World!"

//使用顺序存储
// 利用存储的地址来描述数据的关系。

void foo() {
    char szBuf[] = "Hello World!";

}

//使用非顺序存储
// 自己去描述数据的关系。

// 节点，利用节点中的指针来描绘节点的关系
struct CNode {
    CNode* pPre;
    CNode* pNext;
    char ch;
};


int main()
{
    foo();

    return 0;
}

