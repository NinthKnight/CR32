// Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>

#define INVINCIBLE_ADDR 0x00403616


bool ChangeMemory(HANDLE hProcess, LPVOID lpAddr, BYTE btCode) {

	//权限 改变内存页面属性（1页 ==4kb）
	DWORD flOldProtect;
	BOOL bRet = VirtualProtectEx(hProcess,
		lpAddr,
		1,
		PAGE_EXECUTE_READWRITE,
		&flOldProtect);

	//读进程的内存数据
	BYTE readCode = 0;
	SIZE_T readedBytes = 0;
	SIZE_T writedBytes = 0;

	bRet = ReadProcessMemory(hProcess,
		lpAddr,
		&readCode,
		sizeof(BYTE),
		&readedBytes);

	if (!bRet) {
		return false;
	}


	//写进程的内存数据
	bRet = WriteProcessMemory(hProcess,
		lpAddr,
		&btCode,
		sizeof(BYTE),
		&writedBytes);

	if (!bRet) {
		return false;
	}

	bRet = VirtualProtectEx(hProcess,
		lpAddr,
		1,
		flOldProtect,
		&flOldProtect);


	return true;
}

//自定义消息

#define WM_MYMSG WM_USER+1


bool SendMyMsg() {

	char* pszBuf = "Hello World!";

	HWND hWnd = FindWindowA(NULL, "Win32Msg");

	//向B进程中申请一段内存空间
	////获取进程id
	DWORD dwPid = 0;
	GetWindowThreadProcessId(hWnd, &dwPid);

	//获取进程句柄
	HANDLE hTarget = OpenProcess(PROCESS_ALL_ACCESS,
		FALSE,
		dwPid);

	//LPVOID lpAddr = VirtualAllocEx(hTarget,
	//	           NULL,
	//	           1,
	//	           MEM_RESERVE,
	//	           PAGE_EXECUTE_READWRITE);

	LPVOID lpAddr = VirtualAllocEx(hTarget,
		NULL,
		1,
		MEM_COMMIT,
		PAGE_EXECUTE_READWRITE);


	//写进程的内存数据
	DWORD writedBytes = 0;
	DWORD dwLength = strlen(pszBuf) + 1;
	BOOL bRet = WriteProcessMemory(hTarget,
		lpAddr,
		pszBuf,
		dwLength,
		&writedBytes);


	if (hWnd != NULL && bRet) {
		SendMessage(hWnd, WM_MYMSG, (WPARAM)lpAddr, (LPARAM)dwLength);
	}
	
	VirtualFreeEx(hTarget,
		lpAddr,
		0,
		MEM_RELEASE);

	return true;
}

bool SendCopyDataMsg() {

	HWND hWnd = FindWindowA(NULL, "Win32Msg");

	COPYDATASTRUCT cds;
	char szBuf[] = "Hello World!";

	cds.lpData = szBuf;
	cds.cbData = sizeof(szBuf);
	cds.dwData = 0x123;

	if (hWnd != NULL) {
		SendMessage(hWnd, WM_COPYDATA, (WPARAM)0x456, (LPARAM)&cds);
	}

	return true;
}


int main()
{
	SendCopyDataMsg();


	////获取进程句柄
	////先拿窗口句柄
	//HWND hWnd = FindWindowA(NULL, "摿孭");

	////获取进程id
	//DWORD dwPid = 0;
	//GetWindowThreadProcessId(hWnd, &dwPid);

	////获取进程句柄
	//HANDLE hGame = OpenProcess(PROCESS_ALL_ACCESS,
	//	FALSE,
	//	dwPid);

	//ChangeMemory(hGame,
	//	(LPVOID)INVINCIBLE_ADDR,
	//	0xeb);

	//CloseHandle(hGame);


    return 0;
}

