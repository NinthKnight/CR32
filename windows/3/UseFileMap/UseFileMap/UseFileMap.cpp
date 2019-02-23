// UseFileMap.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <windows.h>

bool Open() {


	//�����ڴ�ӳ���ļ�����
	HANDLE hFileMap = CreateFileMappingA(
		NULL,
		NULL,
		PAGE_READWRITE,
		0,
		0x1000,
		"CR32_FileMap");

	if (hFileMap == nullptr) {
		return false;
	}

	//2 ӳ���ļ�
	LPVOID lpAddr = MapViewOfFile(
		hFileMap,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		0);

	int n = *(int*)lpAddr;

	UnmapViewOfFile(lpAddr);

	CloseHandle(hFileMap);

	return true;
}


int main()
{
	//Test();
	Open();

	return 0;
}


