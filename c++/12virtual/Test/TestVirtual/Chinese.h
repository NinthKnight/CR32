#pragma once
#include "Person.h"
class CChinese :
    public CPerson
{
public:
    CChinese() {
        m_pVirTable = CChinese::m_VirTable;
    }
    ~CChinese();

    void Speak() {
        printf("CChinese::Speak(\"∫∫”Ô\")\r\n");
    }

    void Eat() {
        printf("CChinese::Eat(÷–≤Õ)\r\n");
    }

    static PFN_VIRTUALCHS m_VirTable[2];
};

