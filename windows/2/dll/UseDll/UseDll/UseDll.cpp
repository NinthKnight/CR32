// UseDll.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>


int main()
{
	HMODULE hDll = LoadLibraryA("TestDll.dll");
	
	if (hDll == NULL) {
		return 0;
	}

	int* addr = (int*)GetProcAddress(hDll, "g_data");

	printf("Before change g_data = %d\r\n", *addr);
	
	system("pause");

	*addr = 0x456;

	printf("After change g_data = %d\r\n", *addr);

	system("pause");
	FreeLibrary(hDll);

    return 0;
}

