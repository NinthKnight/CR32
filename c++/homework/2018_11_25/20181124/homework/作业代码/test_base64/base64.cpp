#pragma once
#include "base64.h"
#include <string.h>
#include <stdlib.h>

const unsigned int BASE64::nLen = 64;

const char BASE64::data[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
 
//编码函数
void BASE64::Base64Encry(void *buf, size_t nLen, char *pszEncTextBuf)
{
  //data指针
  char *pBuf = (char *) buf;

  //3 * 8 = 24 位操作区
  BASE64::tagBitOpe BitOpeBuf = { 0 };

  //得到组数
  size_t nGroupCount = nLen / 3;

  //剩余字节数
  size_t nResidueBytes = nLen % 3;

  //计算加密后的文本长度
  size_t nBase64TextLen = (nGroupCount + ((nResidueBytes == 0) ? 0 : 1)) * 4;

  //base64加密文本缓冲区
  char *pszBase64Text = NULL;

  pszBase64Text = (char *) ::malloc(nBase64TextLen);
  if (pszBase64Text == NULL)
  {
    goto EXIT_PROC;
  }

  //前面部分的base64
  for (size_t i = 0,j = 0; i < (nGroupCount * 3); i = i + 3, j = j + 4)
  {
    ::memcpy(&BitOpeBuf, &pBuf[i], 3);
    pszBase64Text[j + 0] = BASE64::data[BitOpeBuf.one];
    pszBase64Text[j + 1] = BASE64::data[BitOpeBuf.two];
    pszBase64Text[j + 2] = BASE64::data[BitOpeBuf.three];
    pszBase64Text[j + 3] = BASE64::data[BitOpeBuf.four];
  }

  //尾部处理
  if (nResidueBytes > 0)
  {
    BitOpeBuf = { 0 };
    ::memcpy(&BitOpeBuf, &pBuf[nGroupCount * 3], nResidueBytes);
    pszBase64Text[nGroupCount * 4 + 0] = BitOpeBuf.one == 0 ? '=' : BASE64::data[BitOpeBuf.one];
    pszBase64Text[nGroupCount * 4 + 1] = BitOpeBuf.two == 0 ? '=' : BASE64::data[BitOpeBuf.two];
    pszBase64Text[nGroupCount * 4 + 2] = BitOpeBuf.three == 0 ? '=' : BASE64::data[BitOpeBuf.three];
    pszBase64Text[nGroupCount * 4 + 3] = BitOpeBuf.four == 0 ? '=' : BASE64::data[BitOpeBuf.four];
  }
  

  //拷贝结果
  ::memcpy(pszEncTextBuf, pszBase64Text, nBase64TextLen);

EXIT_PROC:  //退出处理程序
  if (pszBase64Text != NULL)
  {
    ::free(pszBase64Text);
    pszBase64Text = NULL;
  }

  return;
}

//解码函数
void BASE64::Base64Decry(char *EncText, void *buf, size_t nLen)
{
  //暂不需要
}