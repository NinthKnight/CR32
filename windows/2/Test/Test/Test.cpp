// Test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <windows.h>

#define INVINCIBLE_ADDR 0x00403616


bool ChangeMemory(HANDLE hProcess, LPVOID lpAddr, BYTE btCode) {

	//Ȩ�� �ı��ڴ�ҳ�����ԣ�1ҳ ==4kb��
	DWORD flOldProtect;
	BOOL bRet = VirtualProtectEx(hProcess,
		lpAddr,
		1,
		PAGE_EXECUTE_READWRITE,
		&flOldProtect);

	//�����̵��ڴ�����
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


	//д���̵��ڴ�����
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

//�Զ�����Ϣ

#define WM_MYMSG WM_USER+1


bool SendMyMsg() {

	char* pszBuf = "Hello World!";

	HWND hWnd = FindWindowA(NULL, "Win32Msg");

	//��B����������һ���ڴ�ռ�
	////��ȡ����id
	DWORD dwPid = 0;
	GetWindowThreadProcessId(hWnd, &dwPid);

	//��ȡ���̾��
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


	//д���̵��ڴ�����
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


	////��ȡ���̾��
	////���ô��ھ��
	//HWND hWnd = FindWindowA(NULL, "���P");

	////��ȡ����id
	//DWORD dwPid = 0;
	//GetWindowThreadProcessId(hWnd, &dwPid);

	////��ȡ���̾��
	//HANDLE hGame = OpenProcess(PROCESS_ALL_ACCESS,
	//	FALSE,
	//	dwPid);

	//ChangeMemory(hGame,
	//	(LPVOID)INVINCIBLE_ADDR,
	//	0xeb);

	//CloseHandle(hGame);


    return 0;
}

