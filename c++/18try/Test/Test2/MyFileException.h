#pragma once
#include <string>
#include "MyException.h"

class CMyFileException : public CMyException
{
public:
    enum FILE_EXCPT_TYPE{
        FILE_EXCPT_OPEN, //打开失败
        FILE_EXCPT_READ, //读文件失败
        FILE_EXCPT_WRITE, //写文件失败
    };


    CMyFileException(FILE_EXCPT_TYPE type, std::string str = "文件错误");
    ~CMyFileException();


    FILE_EXCPT_TYPE m_Type;

};

