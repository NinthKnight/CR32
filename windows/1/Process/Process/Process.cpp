// Process.cpp : �������̨Ӧ�ó������ڵ㡣
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


	//��������
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

	//���ô��ھ��
	HWND hWnd = FindWindowA(NULL, "������");

	//��ȡ����id
	DWORD dwPid = 0;
	GetWindowThreadProcessId(hWnd, &dwPid);

	//��ȡ���̾��
	HANDLE hCalc = OpenProcess(PROCESS_ALL_ACCESS,
		        FALSE,
		         dwPid);

	//�رս���
	if (hCalc != NULL) {
		TerminateProcess(hCalc, 0);
	}
	


    return 0;
}

