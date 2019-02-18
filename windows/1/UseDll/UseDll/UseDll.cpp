// UseDll.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>


int main()
{
	HMODULE hDll = LoadLibraryA("TestDll.dll");
	hDll = LoadLibraryA("TestDll.dll");

	FreeLibrary(hDll);
	FreeLibrary(hDll);

    return 0;
}

