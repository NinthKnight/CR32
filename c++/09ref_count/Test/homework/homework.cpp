// work2_20181128.cpp: 定义控制台应用程序的入口点。
//举例说明关键字=default,=delete在类中的作用。

#include "stdafx.h"
#include <iostream>
#include <sstream>

//stl string
//mfc CString
//Qt QString



int main()
{
    std::stringstream ss;

    ss << "Hello" << 1 << "World";

    std::string str;// = "Hello World!";

    std::wstring wstr = L"123";

    //std::getline(ss, str);


    //str[0] = 'A';

    //str.append("123");
    //str += "123";
    //str = str - "123";

   
    //int nIndex = str.find("Hello", 1);

    //if (nIndex == std::string::npos) {
    //    return 0;
    //}



    const char* p = str.c_str();

    std::cout << p << std::endl;


    return 0;
}

