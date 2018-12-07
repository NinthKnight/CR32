/*实现MyString有成员函数MyString* stringcat(MyString *pString)
即为一般的字符串连接,
类和它的子类MyNumString(顾名思义，里面只能是数字串),其中它的连接函数要用加法加起来，比如23,和34的话，它
们连接起来就是57了，不是2334。请编程并实现它们的多态性.*/
#include <iostream>

class CMyString
{
public:
    char m_pString[100] = "abc";
public:
    CMyString* stringcat(CMyString *pString) 
    {
        strcat(m_pString+strlen(m_pString), pString->m_pString);
        return (CMyString*)0;
    }
    virtual CMyString* stringcat(int iAdd1, int iAdd2) 
    { 
        return (CMyString*)0; 
    }
};

class CMyNumString : public CMyString
{
public:
    CMyString* stringcat(int iAdd1, int iAdd2) 
    {
        
        char tmpString[100];
        
        _itoa_s(iAdd1+ iAdd2, tmpString, 10);
        strcpy(m_pString, tmpString);
        return (CMyString*)0;
    }
};

int main()
{
    CMyString str;
    CMyString str1;
    CMyNumString ns1;


    str.stringcat(&str1);
    ((CMyString*)&ns1)->stringcat(12,34);


    std::cout << str.m_pString << std::endl;
    std::cout << ns1.m_pString << std::endl;
    return 0;
}