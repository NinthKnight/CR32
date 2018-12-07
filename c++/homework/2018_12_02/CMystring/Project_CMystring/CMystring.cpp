#include "CMystring.h"
#include <iostream>
#include <stdarg.h>

#pragma warning(disable:4996)

CMystring::~CMystring()
{
  ReleaseSelf();
}

CMystring & CMystring::operator=(CMystring & mString)
{
  SetStr(mString.GetStr());
  return *this;
}

CMystring & CMystring::operator=(const char * pStr)
{
  SetStr(pStr);
  return *this;
}

inline int CMystring::GetBufferSize() const
{
  return this->m_nBuffLen;
}

inline int CMystring::GetStrlen() const
{
  return this->m_nStrLen;
}

int CMystring::Format(const char * strFormat, ...)
{
  char buf[1024] = { 0 };
  int tail = 0;

  va_list vl;
  va_start(vl, strFormat);
  const char *pFmt = strFormat;

  //格式化
  while (*pFmt != '\0')
  {
    if (*pFmt == '%')
    {
      char tBuf[256] = { 0 };
      int n = 0;
      char ch = 0;

      switch (*++pFmt)
      {
      case 'd':
        n = va_arg(vl, int);//检索
        itoa(n, tBuf, 10);
        ::strcat(buf, tBuf);
        tail = tail + strlen(tBuf);
        break;
      case 'c':
        ch = va_arg(vl, char);
        buf[tail++] = ch;
        break;
      case 's':
        const char *str = va_arg(vl, const char *);
        ::strcat(buf, str);
        tail = tail + strlen(str);
        break;
      }
    }
    else
    {
      buf[tail++] = *pFmt;
    }

    pFmt++;
  }
  va_end(vl);

  //拷贝到自己的缓冲区
  SetStr(buf);

  return 0;
}

int CMystring::Cmp(const char * strSrc) const
{
  return ::strcmp(m_pStr, strSrc);
}

int CMystring::Cmp(const CMystring & strCmp) const
{
  return Cmp(strCmp.GetStr());
}

char * CMystring::GetBuffer(int nMinBuffLen)
{
  return nullptr;
}

char * CMystring::GetStr() const
{
  return this->m_pStr;
}

int CMystring::SetStr(const char * strSrc)
{
  //是否是拷贝构造的
  if (m_pRef->isSingle() == true)
  {
    //初始化新的字符串
    InitStr(strSrc);
  }
  else 
  {
    int nLen = ::strlen(strSrc) + 1;

    if (nLen <= m_nBuffLen)
    {
      memcpy(m_pStr, strSrc, nLen);

      m_nStrLen = nLen;
    }
    else
    {
      ReleaseSelf();

      m_pStr = new char[nLen] { 0 };

      memcpy(m_pStr, strSrc, nLen);

      m_nBuffLen = nLen;

      m_nStrLen = nLen;
    }
  }

  return 0;
}

void CMystring::Cat(const char * strCat)
{
  if (strCat == nullptr) return;

  //是否是拷贝构造
  if (m_pRef->isSingle() == false)
  {
    char *strSrc = m_pStr;
    //初始化自己的空间自己的字符串
    InitStr(strSrc);
    //递归再调用一次
    Cat(strCat);
  }
  else
  {
    int nLen = strlen(strCat) + 1;

    int nNewLen = nLen + m_nStrLen;

    if (nNewLen > m_nBuffLen)
    {
      char *buf = new char[nNewLen] { 0 };

      //扩充
      if (m_pStr != nullptr)
      {
        ::strcat(buf, m_pStr);
        ::strcat(buf, strCat);

        //释放
        delete[] m_pStr;
      }
      else
      {
        ::strcat(buf, strCat);
      }

      m_pStr = new char[nNewLen + INITSIZE]{ 0 };
      memcpy(m_pStr, buf, nNewLen);

      m_nBuffLen = nNewLen + INITSIZE;
      m_nStrLen = nNewLen - 1;

      delete[] buf;
    }
    else
    {
      ::strcat(m_pStr, strCat);
      m_nStrLen = nNewLen - 1;
    }
  }

}

void CMystring::Cat(const CMystring & strCat)
{
  Cat(strCat.GetStr());
}

void CMystring::InitSelf()
{
  if (m_pStr == nullptr)
  {
    m_nBuffLen = INITSIZE;
    m_nStrLen = 0;
    m_pStr = new char[INITSIZE] { 0 };
  }

  if (m_pRef == nullptr)
  {
    m_pRef = new CRefCount();
  }
}

void CMystring::ReleaseSelf()
{
  if (m_pRef->Dec() == false)
  {
    m_pStr = nullptr;
    m_nBuffLen = 0;
    m_nStrLen = 0;
    return;
  }

  if (m_pRef != nullptr)
  {
    delete m_pRef;
  }

  if (m_pStr != nullptr)
  {
    unsigned int flag = *((unsigned int *)m_pStr - 1);

    if (flag == 0xfdfdfdfd) //前溢标识检测
    {
      delete[] m_pStr;
      m_pStr = nullptr;
      m_nBuffLen = 0;
      m_nStrLen = 0;
    }
  }
}

void CMystring::ToUpper()
{
  for (int i = 0; i < m_nStrLen; i++)
  {
    if (m_pStr[i] >= 'a' && m_pStr[i] >= 'z')
    {
      m_pStr[i] = m_pStr[i] + 32;
    }
  }
}

void CMystring::ToLower()
{
  for (int i = 0; i < m_nStrLen; i++)
  {
    if (m_pStr[i] >= 'A' && m_pStr[i] >= 'Z')
    {
      m_pStr[i] = m_pStr[i] - 32;
    }
  }

}

/*
  浅拷贝
*/
CMystring::CMystring(CMystring &mString)
{
  m_pStr = mString.GetStr();

  m_nBuffLen = mString.GetBufferSize();

  m_nStrLen = mString.GetStrlen();

  m_pRef = mString.m_pRef;

  m_pRef->Add();
}

CMystring::CMystring(const char * pStr)
{
  InitStr(pStr);
}

CMystring::CMystring()
{
  m_pStr = nullptr;
  InitSelf();
  //cpFlag = false;
}

void CMystring::InitStr(const char * strSrc)
{
  int nLen = ::strlen(strSrc) + 1;

  m_pStr = new char[nLen] { 0 };

  memcpy(m_pStr, strSrc, nLen);

  m_nBuffLen = nLen;

  m_nStrLen = nLen;

  m_pRef = new CRefCount();
}