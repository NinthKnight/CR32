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

    //�麯��
    void Speak() {
        printf("CPerson::Speak(�˻�)\r\n");
    }

    void Eat() {
        printf("CPerson::Eat(����)\r\n");
    }

    static PFN_VIRTUAL m_VirTable[2];
    void* m_pVirTable;
    int m_nGender;
};

