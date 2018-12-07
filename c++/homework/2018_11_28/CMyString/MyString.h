#pragma once
class CMyString
{
private:
    int m_nBuffLen;
    int m_nStrLen;
    char *m_pStr;

public:
    CMyString();
    CMyString(const char *pStr);
    CMyString(CMyString &obj);
    ~CMyString();

    CMyString &operator=(const char *pStr);
    CMyString &operator+(const char *pStr);
    CMyString &operator+=(const char *pStr);
    /* 返回当前缓冲区大小*/
    int GetBufferSize() const;

    /* 返回当前字符串长度*/
    int GetStrlen() const;

    /* 格式化字符串，功能类似于printf，但是结果保存在m_pStr中*/
    int Format(const char* strFormat, ...);

    /*
    CMystring str;
    str.Format("%s:%d", "127.0.0.1", "8080");
    "127.0.0.1:8080"
    */

    /* 比较字符串，参考strcmp */
    int Cmp(const char* strSrc) const;
    int Cmp(const CMyString &strCmp) const;

    /* 返回一个缓冲区，其大小最少为nMinBuffLen(可以大于nMinBuffLen)。如果GetBuffer(0)，则返回
    当前缓冲区*/
    char* GetBuffer(int nMinBuffLen);

    /* 获取当前m_pStr*/
    char* GetStr() const;

    /* 设置CMyString字符串(注意考虑新设置的字符串strSrc大于当前缓冲区的情况)*/
    int SetStr(const char* strSrc);

    /* 连接strCat到当前对象，类似strcat*/
    void Cat(const char* strCat);
    void Cat(const CMyString &strCat);

    /* 初始化自身（已有实现参考）*/
    void InitSelf();
    /* 释放自身（已有实现参考） */
    void ReleaseSelf();

    /* 将字符串全部转为大写 */
    void ToUpper();
    /* 将字符串全部转为小写 */
    void ToLower();


};

