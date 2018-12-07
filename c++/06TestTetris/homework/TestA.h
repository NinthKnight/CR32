#pragma once
#include <iostream>
#include "TestB.h"

class CTestA
{
public:
    void foo() {
        std::cout << "class CTestA:foo" << std::endl;
        //CTestB* p = pTestB;
        //p->foo();
    }
};

