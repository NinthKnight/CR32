#include "stdafx.h"
#include "MyString.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>



CMyString::CMyString()
{
    InitSelf();
}

CMyString::CMyString(const char *pStr)
{
    SetStr(pStr);
    //m_nStrLen = strlen(pStr);
    //m_nBuffLen = m_nStrLen + 1;
    //m_pStr = new char[m_nBuffLen];
    //strcpy_s(m_pStr, m_nBuffLen, pStr);
}

CMyString::CMyString(CMyString & obj)
{
    memcpy_s(this, sizeof(CMyString), &obj, sizeof(obj));
    m_pStr = nullptr;
    m_pStr = new char[obj.m_nBuffLen];
    memcpy_s(m_pStr, m_nBuffLen, obj.m_pStr, obj.m_nBuffLen);
}


CMyString::~CMyString()
{
    ReleaseSelf();
}

CMyString & CMyString::operator=(const char * pStr)
{
    SetStr(pStr);
    return *this;
}

CMyString & CMyString::operator+(const char * pStr)
{
    Cat(pStr);
    return *this;
}

CMyString & CMyString::operator+=(const char * pStr)
{
    Cat(pStr);
    return *this;
}

/* ���ص�ǰ��������С*/
int CMyString::GetBufferSize() const
{
    return m_nBuffLen;
}

/* ���ص�ǰ�ַ�������*/
int CMyString::GetStrlen() const
{
    return m_nStrLen;
}

/* ��ʽ���ַ���������������printf�����ǽ��������m_pStr��*/
int CMyString::Format(const char * strFormat, ...)
{
    va_list argList;
    va_start(argList, strFormat);
    size_t nSize = 10240;
    char *pst = new char[nSize];
    vsprintf_s(pst, nSize, strFormat, argList);
    va_end(argList);
    ReleaseSelf();
    SetStr(pst);
    delete[] pst;

    return 0;
}


/* �Ƚ��ַ������ο�strcmp */
int CMyString::Cmp(const char * strSrc) const
{
    return strcmp(this->m_pStr, strSrc);
}

/* �Ƚ��ַ������ο�strcmp */
int CMyString::Cmp(const CMyString & strCmp) const
{
    return strcmp(this->m_pStr, strCmp.m_pStr);
}

/* ����һ�������������С����ΪnMinBuffLen(���Դ���nMinBuffLen)�����GetBuffer(0)���򷵻�
��ǰ������*/
char * CMyString::GetBuffer(int nMinBuffLen)
{
    if (m_nBuffLen < nMinBuffLen)
    {
        char *pstr = new char[nMinBuffLen];
        if (m_nBuffLen != 0)
        {
            memcpy_s(pstr, nMinBuffLen, m_pStr, m_nBuffLen);
        }
        delete[] m_pStr;
        m_pStr = pstr;
        m_nBuffLen = nMinBuffLen;
    }
    return m_pStr;
}

/* ��ȡ��ǰm_pStr*/
char * CMyString::GetStr() const
{
    return m_pStr;
}

/* ����CMyString�ַ���(ע�⿼�������õ��ַ���strSrc���ڵ�ǰ�����������)*/
int CMyString::SetStr(const char * strSrc)
{
    ReleaseSelf();
    m_nStrLen = strlen(strSrc);
    m_nBuffLen = m_nStrLen + 1;
    m_pStr = new char[m_nBuffLen];
    memcpy_s(m_pStr, m_nBuffLen, strSrc, m_nBuffLen);

    return 0;
}

/* ����strCat����ǰ��������strcat*/
void CMyString::Cat(const char * strCat)
{
    size_t nLength = strlen(strCat) + 1;
    size_t nBuffLength = nLength + m_nBuffLen - 1;
    char *pStr = new char[nBuffLength];
    memset(pStr, 0, nBuffLength);
    sprintf_s(pStr, nBuffLength, "%s%s", m_pStr, strCat);

    delete[] m_pStr;
    m_pStr = nullptr;
    m_pStr = pStr;
    m_nBuffLen = nBuffLength;
    m_nStrLen = nBuffLength - 1;

}

/* ����strCat����ǰ��������strcat*/
void CMyString::Cat(const CMyString & strCat)
{
    size_t nLength = strlen(strCat.GetStr()) + 1;
    size_t nBuffLength = nLength + m_nBuffLen - 1;
    char *pStr = new char[nBuffLength];
    memset(pStr, 0, nBuffLength);
    sprintf_s(pStr, nBuffLength, "%s%s", m_pStr, strCat.GetStr());

    delete[] m_pStr;
    m_pStr = nullptr;
    m_pStr = pStr;
    m_nBuffLen = nBuffLength;
    m_nStrLen = nBuffLength - 1;
}

/* ��ʼ����������ʵ�ֲο���*/
void CMyString::InitSelf()
{
    m_nBuffLen = 0;
    m_nStrLen = 0;
    m_pStr = nullptr;
}

/* �ͷ���������ʵ�ֲο��� */
void CMyString::ReleaseSelf()
{
    if (m_pStr != nullptr)
    {
        delete[] m_pStr;
        m_pStr = nullptr;
    }
}

/* ���ַ���ȫ��תΪ��д */
void CMyString::ToUpper()
{
    _strupr_s(this->m_pStr, m_nBuffLen);
}

/* ���ַ���ȫ��תΪСд */
void CMyString::ToLower()
{
    _strlwr_s(this->m_pStr, m_nBuffLen);
}
