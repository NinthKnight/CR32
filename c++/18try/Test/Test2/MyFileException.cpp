#include "stdafx.h"
#include "MyFileException.h"


CMyFileException::CMyFileException(FILE_EXCPT_TYPE type, std::string str)
{
    m_Type = type;
    m_errInfo = str;
}


CMyFileException::~CMyFileException()
{
}
