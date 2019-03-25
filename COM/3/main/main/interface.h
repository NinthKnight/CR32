#pragma once
#include <windows.h>


//CAD 
class IInterface
{
public:
    virtual void* QueryInterface(const GUID* iid) = 0;
};

typedef IInterface* (*GET_CLASS_OBJECT)();

IInterface* GetClassObject();

// {35F9AA38-8275-4fa2-8245-67EE5BE56565}
static const GUID IID_ISuperMath =
{ 0x35f9aa38, 0x8275, 0x4fa2,{ 0x82, 0x45, 0x67, 0xee, 0x5b, 0xe5, 0x65, 0x65 } };


//接口不变原则
class ISuperMath :public IInterface
{
public:
    virtual int Add(int n1, int n2) = 0;
    virtual int Sub(int n1, int n2) = 0;  
};

class ISuperMath2 :public ISuperMath
{
public:
    virtual int Mul(int n1, int n2) = 0;
};