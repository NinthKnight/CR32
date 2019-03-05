// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <PROCESS.H>

//Í¬²½
DWORD ThreadFunc(LPVOID lpParam) {
  
  while(true){
    Sleep(1000);
    printf("ThreadFunc:5678\r\n");
  }


  return 0;
}



int main(int argc, char* argv[])
{
  HANDLE hThread = (HANDLE)_beginthreadex(
    NULL,
    0,
    (unsigned int (__stdcall *)(void *))ThreadFunc,
    NULL,
    0, //¹ÒÆð
    NULL);


  while(true){
    Sleep(1000);
    printf("main:1234\r\n");
  }


  DWORD dwRet = WaitForSingleObject(hThread,
        INFINITE);
	
	return 0;
}

