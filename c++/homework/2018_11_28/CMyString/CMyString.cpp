// CMyString.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "MyString.h"


int main()
{
    CMyString str1 = "hello1";
    std::cout << str1.GetStr() << "\tStrlen:" << str1.GetStrlen() << "\tBuffSize:" << str1.GetBufferSize() << std::endl;

    CMyString str2("hello2");
    std::cout << str2.GetStr() << "\tStrlen:" << str2.GetStrlen() << "\tBuffSize:" << str2.GetBufferSize() << std::endl;

    str2 = "hello3";
    std::cout << str2.GetStr() << "\tStrlen:" << str2.GetStrlen() << "\tBuffSize:" << str2.GetBufferSize() << std::endl;

    str2.SetStr("hello4");
    std::cout << str2.GetStr() << "\tStrlen:" << str2.GetStrlen() << "\tBuffSize:" << str2.GetBufferSize() << std::endl;

    str2.Cat(" word!");
    std::cout << str2.GetStr() << " Strlen:" << str2.GetStrlen() << "\tBuffSize:" << str2.GetBufferSize() << std::endl;

    str2 = "hello";
    str2 = str2 + " word!";
    std::cout << str2.GetStr() << "\tStrlen:" << str2.GetStrlen() << "\tBuffSize:" << str2.GetBufferSize() << std::endl;

    str2 = "hello";
    str2 += " word!";
    std::cout << str2.GetStr() << "\tStrlen:" << str2.GetStrlen() << "\tBuffSize:" << str2.GetBufferSize() << std::endl;

    CMyString str3 = str1;
    std::cout << str3.GetStr() << "\tStrlen:" << str3.GetStrlen() << "\tBuffSize:" << str3.GetBufferSize() << std::endl;
    CMyString str4;
    str4.Format("%s\tStrlen:%d\tBuffSize:%d", str3.GetStr(), str3.GetStrlen(), str3.GetBufferSize());
    std::cout << str4.GetStr() << std::endl;

    system("pause");
    return 0;
}

