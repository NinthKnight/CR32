// TestHttp.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "SkyChaserHttp.h"
#include <fstream>
#include <iostream>
#include "MyThreadPlool.h"

int main()
{
    CSkyChaserHttp http;
    string strRet;

    http.sc_appendHeader("Connection: close");
    http.sc_appendHeader("Pragma: no-cache");
    http.sc_appendHeader("Cache-Control: no-cache");
    http.sc_appendHeader("Upgrade-Insecure-Requests: 1");
    http.sc_appendHeader("User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/68.0.3440.84 Safari/537.36");
    http.sc_appendHeader("Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*; q = 0.8");
    http.sc_appendHeader("Accept-Encoding: gzip, deflate");
    http.sc_appendHeader("Accept-Language: zh-CN,zh;q=0.9");

    std::ifstream fin("dictionary.txt");
    char szHttp[256] = "www.51asm.com/";
    char szTemp[256] = "";
    char szSpell[256] = { 0 };

    MyThreadPlool *ThPool = new MyThreadPlool();
    ThPool->Create();

    char temp[20] = { 0 };
    std::string tempString;

    //for (int i = 0; i < 1000; ++i)
    //{
    //    _itoa_s(i, temp, 10);
    //    tempString = temp;
    //    ThPool->addTask(tempString);
    //}

    //ThPool->Destroy();
    //ThPool->getTask();
    while (!fin.eof())
    {
        fin.getline(szTemp, 100);
        strcat_s(szSpell, szHttp);
        strcat_s(szSpell, szTemp);
        //printf("%s\r\n", szTemp);

        //CURLcode code = http.sc_get(szSpell, strRet);
        ThPool->addTask(szSpell);

        memset(szSpell, 0, sizeof(szSpell));
    }

	return 0;
}

