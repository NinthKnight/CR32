// TestTry.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <excpt.h>
#include <DbgHelp.h>

using namespace std;
//异常
//读写异常， 除0，内存申请失败

//错误
 
//void foo() {
//    FILE* fp = fopen("1.txt", "rb");
//    if (fp == NULL) {
//        goto EXIT;
//    }
//
//EXIT:
//    //clear
//}

//void foo_test() {
//    try {
//        FILE* fp = 打开文件("1.txt", "rb");
//        读文件(fp);
//        关闭文件(fp);
//    }
//    catch (...) {
//        异常处理;
//    }
//
//}

//关键字： try throw catch

void Test() throw(int) {

    //terminate();
    //abort();
    throw 1; 

    //try {
    //    //try块 业务逻辑

    //    //throw 1;
    //    //throw 抛异常
    //}
    //catch (int n) {
    //    //catch块 处理异常
    //    cout << n << endl;
    //}




}

//当抛出的异常无人处理时，系统会调用UEF.



LONG WINAPI myExceptionHandler(
     _EXCEPTION_POINTERS *ExceptionInfo
    )
{
    MessageBox(NULL, _T("程序错误"), _T("程序遇到错误，请联系开发作者xxx"), NULL);

    cout << hex << ExceptionInfo->ExceptionRecord->ExceptionAddress << endl
         << hex << ExceptionInfo->ContextRecord->Eax << endl;

    HANDLE hFile = CreateFile(_T("1.dmp"),//文件名
                             GENERIC_READ | GENERIC_WRITE, //读写标志
                             FILE_SHARE_READ | FILE_SHARE_WRITE,//共享读写
                             NULL,//安全属性
                             CREATE_NEW,//创建新的
                             FILE_ATTRIBUTE_NORMAL,//文件属性
                             NULL);

    MINIDUMP_EXCEPTION_INFORMATION mei = {0};
    mei.ExceptionPointers = ExceptionInfo;
    mei.ThreadId = GetCurrentThreadId();
    mei.ClientPointers = TRUE;

    BOOL bRet = MiniDumpWriteDump(GetCurrentProcess(),
        GetCurrentProcessId(),
        hFile,
        MiniDumpNormal,
        &mei,
        NULL,
        NULL);

    CloseHandle(hFile);

    return EXCEPTION_EXECUTE_HANDLER;
}

int main()
{
    //替换默认UEF（terminate()）
    //SetUnhandledExceptionFilter(myExceptionHandler);
    
    //try {
    //    char* p = NULL;
    //    if (p == NULL) {
    //        throw 1;
    //    } 
    //}
    //catch (...) {
    //    cout << "catch" << endl;
    //}

    //cout << "catch2" << endl;
    
    Test();
    //try {
    //    
    //}
    //catch (int n) {
    //    cout << n << endl;
    //}

    return 0;
}

