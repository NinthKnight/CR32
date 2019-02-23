// MyCmd.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <iostream>
using namespace std;


//线程回调函数
DWORD WINAPI myThreadFunc(
	LPVOID lpThreadParameter
	) {

	HANDLE hMyWrite = (HANDLE)lpThreadParameter;

	while (true) {
		char line[81];
		cin.getline(line, 81);
		strcat_s(line, "\n");

		//写入到对应的管道中
		DWORD dwWritedBytes = 0;
		BOOL bRet = WriteFile(
			hMyWrite,
			line,
			strlen(line),
			&dwWritedBytes,
			NULL);
	}

	return 0;
}

//创建cmd
bool CreateCmd() {

	//两条管道
	// mycmd       <--->          cmd
	// hMyWrite   ----->      hCmdRead
	// hMyRead    <-----     hCmdWrite

	HANDLE hMyWrite = NULL;
	HANDLE hCmdRead = NULL;

	HANDLE hMyRead = NULL;
	HANDLE hCmdWrite = NULL;

	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = true;
	sa.lpSecurityDescriptor = nullptr;

	BOOL bRet = CreatePipe(
		&hCmdRead,
		&hMyWrite,
		&sa,
		0);
	if (!bRet) {
		return false;
	}

	bRet = CreatePipe(
		&hMyRead,
		&hCmdWrite,
		&sa,
		0);
	if (!bRet) {
		return false;
	}

	char szBuf[256] = "cmd.exe";

	STARTUPINFOA si = { 0 };
	si.cb = sizeof(STARTUPINFOA);

	si.dwFlags = STARTF_USESTDHANDLES;
	si.hStdInput = hCmdRead;
	si.hStdOutput = hCmdWrite;
	si.hStdError = hCmdWrite;

	PROCESS_INFORMATION pi = { 0 };

	//创建进程
	bRet = CreateProcessA(NULL,
		           szBuf,
		           NULL,
		           NULL,
		           TRUE,
		           CREATE_NO_WINDOW,
		           NULL,
		           NULL,
		           &si,
		           &pi);

	if (!bRet) {
		return false;
	}

	//开辟一个写线程
	HANDLE hThread = CreateThread(
		NULL,
		0,
		myThreadFunc,
		(LPVOID)hMyWrite,
		0, //CREATE_SUSPENDED 挂起,
		NULL);


	DWORD dwBytesRead = 0;            // number of bytes read
	DWORD dwTotalBytesAvail = 0;      // number of bytes available
	DWORD dwBytesLeftThisMessage = 0;  // unread bytes

	
	while (true) {
		DWORD dwReadedBytes = 0;
		dwBytesRead = 0;            // number of bytes read
		dwTotalBytesAvail = 0;      // number of bytes available
		dwBytesLeftThisMessage = 0;  // unread bytes
		memset(szBuf, 0, 256);

		bRet = PeekNamedPipe(
			hMyRead,
			NULL,
			0,
			&dwBytesRead,
			&dwTotalBytesAvail,
			&dwBytesLeftThisMessage);

		if (!bRet) {
			break;
		}

		if (dwTotalBytesAvail > 0){
			bRet = ReadFile(hMyRead,
				szBuf,
				255,
				&dwReadedBytes,
				NULL);


			printf(szBuf);
			if (!bRet){
				break;
			}
		}
			
	}

	return true;

}


int main()
{
	CreateCmd();

    return 0;
}

