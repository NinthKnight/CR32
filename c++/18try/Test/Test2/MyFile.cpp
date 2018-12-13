#include "stdafx.h"
#include "MyFile.h"


CMyFile::CMyFile()
{
}


CMyFile::~CMyFile()
{
}

void CMyFile::Open(char* pszFileName) {

    m_pFile = fopen(pszFileName, "rb+");
    if (m_pFile == NULL) {
        throw CMyFileException(CMyFileException::FILE_EXCPT_OPEN, pszFileName);
    }
}