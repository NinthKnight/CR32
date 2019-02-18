// Process.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>


int main()
{
	ExitProcess(0);
	//1 winexec

	//WinExec("notepad.exe", SW_SHOW);
	//2 ShellExecute

	//ShellExecuteA(NULL, "open", "http://www.51asm.com", NULL, NULL, SW_SHOWNORMAL);

	//ShellExecuteA(NULL, "explore", "H:\\CR32\\windows\\1", NULL, NULL, SW_SHOWNORMAL);

	char szBuf[256] = "notepad.exe D:\\123.txt";

	STARTUPINFOA si = {0};
	si.cb = sizeof(STARTUPINFOA);

	PROCESS_INFORMATION pi = { 0 };


	//创建进程
	//BOOL bRet = CreateProcessA(NULL,
	//	           szBuf,
	//	           NULL,
	//	           NULL,
	//	           FALSE,
	//	           CREATE_NEW_CONSOLE,
	//	           NULL,
	//	           NULL,
	//	           &si,
	//	           &pi);

	//先拿窗口句柄
	HWND hWnd = FindWindowA(NULL, "计算器");

	//获取进程id
	DWORD dwPid = 0;
	GetWindowThreadProcessId(hWnd, &dwPid);

	//获取进程句柄
	HANDLE hCalc = OpenProcess(PROCESS_ALL_ACCESS,
		        FALSE,
		         dwPid);

	//关闭进程
	if (hCalc != NULL) {
		TerminateProcess(hCalc, 0);
	}
	


    return 0;
}

