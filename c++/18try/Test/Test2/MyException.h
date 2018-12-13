#pragma once
#include <string>

class CMyException
{
public:
    CMyException();
    ~CMyException();

    const char* what() {
        return m_errInfo.c_str();
    }

protected:
    std::string m_errInfo;
};

