// Test2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "MyFile.h"

//1. 异常可以嵌套
//2. 抛出的异常有类型匹配，没有隐式转换
//3. ...表示任意类型的异常

void Test(){

    try {
        try {
            throw 1.0f;
        }
        catch (int) {
            printf("catch (int)\r\n");
        }
    }
    catch (...) {
        printf("catch (...)\r\n");
    }


}


void foo() {
    CMyFile f;
    try {
        f.Open("123");

    }
    //catch (CMyFileException& e) {
    //    if (e.m_Type == CMyFileException::FILE_EXCPT_OPEN) {
    //        printf("打开%s文件失败" , e.what());
    //    }
    //}
    catch (CMyException& e) {
        printf("错误：%s", e.what());
    }
  
}

int main()
{
    foo();
    //Test();

    return 0;
}

