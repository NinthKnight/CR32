#pragma once
#include <functional>   // std::function, std::negate

class CPerson;
class CChinese;

typedef void(CPerson::*PFN_VIRTUAL)(void);
typedef void(CChinese::*PFN_VIRTUALCHS)(void);

class CPerson
{
public:
    CPerson() {
        m_pVirTable = m_VirTable;
    }
    ~CPerson();

    //虚函数
    void Speak() {
        printf("CPerson::Speak(人话)\r\n");
    }

    void Eat() {
        printf("CPerson::Eat(东西)\r\n");
    }

    static PFN_VIRTUAL m_VirTable[2];
    void* m_pVirTable;
    int m_nGender;
};

