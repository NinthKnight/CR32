#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "base64.h"
#pragma warning(disable:4996)

using namespace std;
using namespace BASE64;

int main(int argc, char *argv[])
{

  fstream fs;
  fstream fsBase64;
  char szBuf[100] = { 0 };

  //打开读入文件
  fs.open("测试账号.txt", fstream::in);
  if (fs.is_open() == false)
  {
    cout << "文件不存在!" << endl;
    goto EXIT_PROC;
  }

  //打开Base64后的文件
  fsBase64.open("Base64账号.txt", fstream::out);
  if (fsBase64.is_open() == false)
  {
    goto EXIT_PROC;
  }

  do
  {
    char *pszAccount = NULL;
    char *pszPassword = NULL;
    char szBase64Pass[128] = { 0 };

    fs.getline(szBuf, 100);
    
    //账号
    pszAccount = ::strtok(szBuf, "----");
    //密码
    pszPassword = ::strtok(NULL, "----");
    if (pszPassword != NULL)
    {
      //输出
      cout << pszPassword << endl;

      //Base64编码
      Base64Encry(pszPassword, strlen(pszPassword), szBase64Pass);

      //写到文件
      fsBase64 << pszAccount << "----" << szBase64Pass << endl;
    }

  } while (!fs.eof());
  
  cout << "Base64 Successfuly!!" << endl;

EXIT_PROC: //退出处理
  fs.close();
  fsBase64.close();

  getchar();
  return 0;
}