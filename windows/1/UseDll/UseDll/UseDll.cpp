// UseDll.cpp : �������̨Ӧ�ó������ڵ㡣
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

