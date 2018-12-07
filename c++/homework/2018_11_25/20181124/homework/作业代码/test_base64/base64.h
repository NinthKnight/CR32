#pragma once

/*
  Base64编码 和 解码
*/
namespace BASE64
{
  //操作区
  struct tagBitOpe
  {
    unsigned int one : 6;
    unsigned int two : 6;
    unsigned int three : 6;
    unsigned int four : 6;
  };

  //数据长度
  extern const unsigned int nLen;

  //字符数据
  extern const char data[];


  //编码函数
  void Base64Encry(void *buf, size_t nLen, char *EncText);

  //解码函数
  void Base64Decry(char *EncText, void *buf, size_t nLen);

}