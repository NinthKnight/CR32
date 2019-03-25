#include "stdafx.h"
#include "SuperMath.h"


CSuperMath::CSuperMath()
{
}


CSuperMath::~CSuperMath()
{
}

void * CSuperMath::QueryInterface(const GUID * iid)
{
    return (ISuperMath2*)this;
}

int CSuperMath::Add(int n1, int n2)
{
    return n1 + n2;
}

int CSuperMath::Sub(int n1, int n2)
{
    return n1 - n2;
}

