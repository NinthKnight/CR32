// TestDll.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"


//dllmain
#pragma data_seg( "MY_DATA" )
int g_data = 123;
#pragma data_seg(  )


#pragma comment(linker, "/SECTION:MY_DATA,RWS")


BOOL WINAPI DllMain(HINSTANCE hinstDLL,  // handle to the DLL module
	DWORD fdwReason,     // reason for calling function
	LPVOID lpvReserved)   // reserved);
{
	OutputDebugStringA("Faked Dll:DllMain!\r\n");

	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH: {
		OutputDebugStringA("Faked Dll:DLL_PROCESS_ATTACH!\r\n");
		return true;
	}
	break;

	case DLL_PROCESS_DETACH: {
		OutputDebugStringA("Faked Dll:DLL_PROCESS_DETACH!\r\n");
		return true;
	}
	break;

	default:
		break;
	}

	return true;
}