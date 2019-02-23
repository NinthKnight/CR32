// TestFileMap.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <windows.h>

//�ļ�ӳ��
//mmap
//CreateFileMapping

bool Test() {

	HANDLE hFile = CreateFileA(
		"ReadMe.txt",
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (hFile == nullptr) {
		return false;
	}

	//�����ڴ�ӳ���ļ�����
	HANDLE hFileMap = CreateFileMappingA(
		hFile,
		NULL,
		PAGE_READWRITE,
		0,
		0,
		NULL);

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

	UnmapViewOfFile(lpAddr);

	CloseHandle(hFileMap);
	CloseHandle(hFile);

	return true;
}

bool Create() {


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

	*(int*)lpAddr = 0x12345678;

	UnmapViewOfFile(lpAddr);

	CloseHandle(hFileMap);

	return true;
}


int main()
{
	//Test();
	Create();

    return 0;
}

