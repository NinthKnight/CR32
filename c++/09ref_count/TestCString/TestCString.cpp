// TestCString.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <AFX.H>

void MyFormat(const char* lpszFormat, ...)
{

  char szBuf[256];
  va_list argList;
  va_start(argList, lpszFormat);
  
//   char* p = va_arg(argList, char*);
//   int n = va_arg(argList, int);
//   char* p2 = va_arg(argList, char*);

  vsprintf(szBuf, lpszFormat, argList);
  
	va_end(argList);

}

int main(int argc, char* argv[])
{

  CString str = "Hello World!";
  CString str2 = str;
  
  //str[0] = 'A';
  //printf("%c", str[0]);

  
  
  str.Format("%s%d%s", "Hello", 1, "World!");

  char szBuf[256] = { 0 };

  MyFormat("%s%d%s", "Hello", 1, "World!");

  //sprintf(szBuf, "%s%d%s", ...);




	return 0;
}
