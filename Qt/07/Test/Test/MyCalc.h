#pragma once

class __declspec(dllexport) CMyCalc
{
public:
    CMyCalc();
    ~CMyCalc();

    int add(int n1, int n2, int n3);
};

extern "C" void MyTest();

__declspec(dllexport) int n;

