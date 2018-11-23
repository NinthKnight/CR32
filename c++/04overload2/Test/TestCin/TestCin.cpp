// TestCin.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
using namespace std;

void foo_screen() {

    char szBuf[256] = {0};
    //产生输入的对象
    //int n = cin.get();
    //istream mycin;
    //iostream obj;
    int n;
    //cin.operator>>(n);

    cin >> n;

    cin.get(szBuf, 256);

    cout.write(szBuf, strlen(szBuf));

    cout << szBuf << endl;

}

void foo_file() {

    //ifstream
    //ofstream
    //fstream
    char szBuf[256] = { 0 };

    fstream fs;
    fs.open("ReadMe.txt");
    if (!fs.is_open()) {
        return;
    }

    int n;
    fs >> n;

    fs.get(szBuf, 256);

    fs.write("Hello", strlen("Hello"));

    fs.close();

}

int main()
{
    //foo_screen();
    foo_file();

    return 0;
}

