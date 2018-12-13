// TestExcept.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

//
void foo() {
    //SEH 异常处理框架

    //__try {
    //
    //}
    //__except() {
    //
    //}

    FILE* fp = NULL;
    char* p = NULL;

    __try {

        fp = fopen("ReadMe.txt", "rb+");
        if (fp == NULL) {
            printf("fp == NULL\r\n");
            __leave;
        }

        p = new char[10];
        if (p == NULL) {
            __leave;
        }

    }
    __finally{

        printf("finally\r\n");

        if (p != NULL) {
            printf("delete[] p\r\n");
            delete[] p;
        }   

        if (fp != NULL) {
            printf("fclose(fp)\r\n");
            fclose(fp);
        }
    }


}


int main()
{
    foo();
    return 0;
}

