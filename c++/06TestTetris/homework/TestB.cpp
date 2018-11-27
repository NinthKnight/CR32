#include "stdafx.h"
#include "TestB.h"
#include "TestA.h"


void CTestB::foo(CTestA* pTestA) {
    std::cout << "class CTestB:foo" << std::endl;
    pTestA->foo();
}
