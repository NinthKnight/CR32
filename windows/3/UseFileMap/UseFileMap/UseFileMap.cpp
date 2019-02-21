// UseFileMap.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>

bool Open() {


	//创建内存映射文件对象
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

	//2 映射文件
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


