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

  //�򿪶����ļ�
  fs.open("�����˺�.txt", fstream::in);
  if (fs.is_open() == false)
  {
    cout << "�ļ�������!" << endl;
    goto EXIT_PROC;
  }

  //��Base64����ļ�
  fsBase64.open("Base64�˺�.txt", fstream::out);
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
    
    //�˺�
    pszAccount = ::strtok(szBuf, "----");
    //����
    pszPassword = ::strtok(NULL, "----");
    if (pszPassword != NULL)
    {
      //���
      cout << pszPassword << endl;

      //Base64����
      Base64Encry(pszPassword, strlen(pszPassword), szBase64Pass);

      //д���ļ�
      fsBase64 << pszAccount << "----" << szBase64Pass << endl;
    }

  } while (!fs.eof());
  
  cout << "Base64 Successfuly!!" << endl;

EXIT_PROC: //�˳�����
  fs.close();
  fsBase64.close();

  getchar();
  return 0;
}