#pragma once

/*
  Base64���� �� ����
*/
namespace BASE64
{
  //������
  struct tagBitOpe
  {
    unsigned int one : 6;
    unsigned int two : 6;
    unsigned int three : 6;
    unsigned int four : 6;
  };

  //���ݳ���
  extern const unsigned int nLen;

  //�ַ�����
  extern const char data[];


  //���뺯��
  void Base64Encry(void *buf, size_t nLen, char *EncText);

  //���뺯��
  void Base64Decry(char *EncText, void *buf, size_t nLen);

}