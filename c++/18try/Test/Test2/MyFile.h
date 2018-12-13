#pragma once
#include "MyFileException.h"

class CMyFile
{
public:
    CMyFile();
    ~CMyFile();

    void Open(char* pszFileName) throw(int, CMyFileException);

private:
    FILE* m_pFile;

};

