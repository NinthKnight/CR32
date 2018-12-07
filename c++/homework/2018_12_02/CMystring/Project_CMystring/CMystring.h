#pragma once
#include "RefCount.h"

class CMystring
{
private:
  void InitStr(const char * strSrc);

public:
  /* ���ص�ǰ��������С*/
  inline int GetBufferSize() const;

  /* ���ص�ǰ�ַ�������*/
  inline int GetStrlen() const;

  /* ��ʽ���ַ���������������printf�����ǽ��������m_pStr��*/
  int Format(const char* strFormat, ...);

  /* �Ƚ��ַ������ο�strcmp */
  int Cmp(const char* strSrc) const;
  int Cmp(const CMystring &strCmp) const;

  /* ����һ�������������С����ΪnMinBuffLen(���Դ���nMinBuffLen)�����GetBuffer(0)���򷵻�
  ��ǰ������*/
  char* GetBuffer(int nMinBuffLen);

  /* ��ȡ��ǰm_pStr
  */
  char* GetStr() const;

  /* ����CMyString�ַ���(ע�⿼�������õ��ַ���strSrc���ڵ�ǰ�����������)*/
  int SetStr(const char* strSrc);

  /* ����strCat����ǰ��������strcat*/
  void Cat(const char* strCat);
  void Cat(const CMystring &strCat);

  /* ��ʼ����������ʵ�ֲο���*/
  void InitSelf();
  /* �ͷ���������ʵ�ֲο��� */
  void ReleaseSelf();

  /* ���ַ���ȫ��תΪ��д */
  void ToUpper();
  /* ���ַ���ȫ��תΪСд */
  void ToLower();

  CMystring(CMystring& mString);

  CMystring(const char *pStr);

  CMystring();

  ~CMystring();

  CMystring& operator=(CMystring& mString);

  CMystring& operator=(const char * pStr);

private:
  int m_nBuffLen;
  int m_nStrLen;
  char *m_pStr;
  CRefCount *m_pRef;//���ü���

  enum
  {
    INITSIZE = 20
  };

};