// dllmain.cpp : ���� DLL Ӧ�ó������ڵ㡣
#include "stdafx.h"
#include "SuperMath.h"


IInterface* GetClassObject()
{
    return new CSuperMath();
}

