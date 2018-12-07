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

/* 返回当前缓冲区大小*/
int CMyString::GetBufferSize() const
{
    return m_nBuffLen;
}

/* 返回当前字符串长度*/
int CMyString::GetStrlen() const
{
    return m_nStrLen;
}

/* 格式化字符串，功能类似于printf，但是结果保存在m_pStr中*/
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


/* 比较字符串，参考strcmp */
int CMyString::Cmp(const char * strSrc) const
{
    return strcmp(this->m_pStr, strSrc);
}

/* 比较字符串，参考strcmp */
int CMyString::Cmp(const CMyString & strCmp) const
{
    return strcmp(this->m_pStr, strCmp.m_pStr);
}

/* 返回一个缓冲区，其大小最少为nMinBuffLen(可以大于nMinBuffLen)。如果GetBuffer(0)，则返回
当前缓冲区*/
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

/* 获取当前m_pStr*/
char * CMyString::GetStr() const
{
    return m_pStr;
}

/* 设置CMyString字符串(注意考虑新设置的字符串strSrc大于当前缓冲区的情况)*/
int CMyString::SetStr(const char * strSrc)
{
    ReleaseSelf();
    m_nStrLen = strlen(strSrc);
    m_nBuffLen = m_nStrLen + 1;
    m_pStr = new char[m_nBuffLen];
    memcpy_s(m_pStr, m_nBuffLen, strSrc, m_nBuffLen);

    return 0;
}

/* 连接strCat到当前对象，类似strcat*/
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

/* 连接strCat到当前对象，类似strcat*/
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

/* 初始化自身（已有实现参考）*/
void CMyString::InitSelf()
{
    m_nBuffLen = 0;
    m_nStrLen = 0;
    m_pStr = nullptr;
}

/* 释放自身（已有实现参考） */
void CMyString::ReleaseSelf()
{
    if (m_pStr != nullptr)
    {
        delete[] m_pStr;
        m_pStr = nullptr;
    }
}

/* 将字符串全部转为大写 */
void CMyString::ToUpper()
{
    _strupr_s(this->m_pStr, m_nBuffLen);
}

/* 将字符串全部转为小写 */
void CMyString::ToLower()
{
    _strlwr_s(this->m_pStr, m_nBuffLen);
}
