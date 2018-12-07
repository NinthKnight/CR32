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
    /* ���ص�ǰ��������С*/
    int GetBufferSize() const;

    /* ���ص�ǰ�ַ�������*/
    int GetStrlen() const;

    /* ��ʽ���ַ���������������printf�����ǽ��������m_pStr��*/
    int Format(const char* strFormat, ...);

    /*
    CMystring str;
    str.Format("%s:%d", "127.0.0.1", "8080");
    "127.0.0.1:8080"
    */

    /* �Ƚ��ַ������ο�strcmp */
    int Cmp(const char* strSrc) const;
    int Cmp(const CMyString &strCmp) const;

    /* ����һ�������������С����ΪnMinBuffLen(���Դ���nMinBuffLen)�����GetBuffer(0)���򷵻�
    ��ǰ������*/
    char* GetBuffer(int nMinBuffLen);

    /* ��ȡ��ǰm_pStr*/
    char* GetStr() const;

    /* ����CMyString�ַ���(ע�⿼�������õ��ַ���strSrc���ڵ�ǰ�����������)*/
    int SetStr(const char* strSrc);

    /* ����strCat����ǰ��������strcat*/
    void Cat(const char* strCat);
    void Cat(const CMyString &strCat);

    /* ��ʼ����������ʵ�ֲο���*/
    void InitSelf();
    /* �ͷ���������ʵ�ֲο��� */
    void ReleaseSelf();

    /* ���ַ���ȫ��תΪ��д */
    void ToUpper();
    /* ���ַ���ȫ��תΪСд */
    void ToLower();


};

