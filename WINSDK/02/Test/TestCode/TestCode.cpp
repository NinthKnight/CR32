// TestCode.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <string>
using namespace std;

char* p1 = "张三";
wchar_t* p2 = L"张三";

WCHAR wszUserName[1] = {0};          // Unicode user name

//Get error msg
void GetLastErrorMsg() {

    //DWORD dw = GetLastError();

    LPVOID lpMsgBuf = nullptr;
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        GetLastError(),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
        (LPTSTR)&lpMsgBuf,
        0,
        NULL
        );

   
    //string str1 = "error 123";
    //wstring str2 = L"error 123";

    //wstring str3 = L"gui 123";
    //OutputDebugStringW(str2.c_str());
    //OutputDebugStringW(str3.c_str());

    OutputDebugString((LPCTSTR)lpMsgBuf);

    //日志形式
    //__FILE__
    //__LINE__

    //MessageBox(NULL, (LPCTSTR)lpMsgBuf, _T("Error"), MB_OK | MB_ICONINFORMATION);
    
    // Free the buffer.
    
    

    LocalFree(lpMsgBuf);

}



//编码转换
wchar_t* GetFullName(char *UserName)
{
    // Convert ANSI user name and domain to Unicode
    int n = MultiByteToWideChar(CP_ACP, 0, UserName,
        strlen(UserName) + 1, wszUserName,
        0);

    wchar_t* pWchar = new wchar_t[n];



    int nRet = MultiByteToWideChar(CP_ACP, 0, UserName,
        strlen(UserName) + 1, pWchar,
        n);

    if (nRet == 0) {
       
        GetLastErrorMsg();



    }

    return wszUserName;
}



int main(){

    GetFullName(p1);


    return 0;
}

