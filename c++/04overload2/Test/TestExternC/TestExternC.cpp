// TestExternC.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "piano_dll_export.h"

#pragma comment(lib, "piano_dll.lib")

int main()
{
    fun_Create(NULL);

    return 0;
}

