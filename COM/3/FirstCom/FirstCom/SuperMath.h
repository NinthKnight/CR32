#pragma once
#include "../../main/main/interface.h"

class CSuperMath :public ISuperMath
{
public:
    CSuperMath();
    ~CSuperMath();

    // ͨ�� ISuperMath �̳�
    virtual void * QueryInterface(const GUID * iid) override;
    virtual int Add(int n1, int n2) override;
    virtual int Sub(int n1, int n2) override;
 
};

