// TestCin.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
using namespace std;

void foo_screen() {

    char szBuf[256] = {0};
    //��������Ķ���
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

