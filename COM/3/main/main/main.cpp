// main.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include "interface.h"
#include <stdlib.h>


int main(int argc, char* argv[])
{
    HMODULE hDll = LoadLibrary("F:\\COM\\3\\FirstCom\\Debug\\FirstCom.dll");
    //check

    GET_CLASS_OBJECT pfnGetClassObject = (GET_CLASS_OBJECT)GetProcAddress(hDll, "GetClassObject");
    //check

    IInterface *pObject = pfnGetClassObject();
    //check

    //获取接口
    ISuperMath *pSuperMath = (ISuperMath*)pObject->QueryInterface(&IID_ISuperMath);
    int result = pSuperMath->Add(1, 2);

    //vtable[0]
    printf("1+2=%d\n", result);
    //result = pSuperMath->Mul(3, 2);

    printf("3*2=%d\n", result);


    system("pause");
    return 0;
}

