#include "stdafx.h"
#include "MyCalc.h"


#pragma comment(linker, "/EXPORT:_MyTest")


CMyCalc::CMyCalc()
{
}


CMyCalc::~CMyCalc()
{
}

int CMyCalc::add(int n1, int n2, int n3)
{
    return n1 + n2;
}

void MyTest() {

    printf("void MyTest()");
}