// Pipe.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>


//pipe
bool UsePipe() {
	HANDLE hReadPipe = NULL;
	HANDLE hWritePipe = NULL;
	
	BOOL bRet = CreatePipe(
		&hReadPipe,
		&hWritePipe,
		NULL,
		0);

	if (!bRet) {
		return false;
	}

	DWORD dwWritedBytes = 0;

	bRet = WriteFile(
		hWritePipe,
		"Hello World!",
		sizeof("Hello World!"),
		&dwWritedBytes,
		NULL);

	char szBuf[256] = { 0 };

	bRet = ReadFile(hReadPipe,
		     szBuf,
		     256,
			&dwWritedBytes,
			NULL);

	CloseHandle(hReadPipe);
	CloseHandle(hWritePipe);

	return true;
}

int main()
{
	UsePipe();
    return 0;
}

