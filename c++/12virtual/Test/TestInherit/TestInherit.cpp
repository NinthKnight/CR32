// TestInherit.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <ctime>

//������󣺶�̬-�麯��
//

class CPerson {
public:
    CPerson() {
        m_nType = 0;
    }

    //�麯��
    virtual void Speak() {
        printf("CPerson::Speak(�˻�)\r\n");
    }

    virtual void Eat() {
        printf("CPerson::Eat(����)\r\n");
    }
    
    int m_nType;
};

class CChinese : public CPerson{
public:
    //R"("123")" ԭʼ�ַ���

    CChinese() {
        m_nType = 1;
    }

    //R"(+Speak("����")+)" ԭʼ�ַ���
    //R"(*CChinese::Speak("����")\r\n*)"
    void Speak() {
        printf("CChinese::Speak(\"����\")\r\n");
    }

    virtual void Eat() {
        printf("CChinese::Eat(�в�)\r\n");
    }



};

class CEnglish : public CPerson {
public:
    //R"("123")" ԭʼ�ַ���

    //R"(+Speak("����")+)" ԭʼ�ַ���
    //R"(*CChinese::Speak("����")\r\n*)"
    CEnglish() {
        m_nType = 2;
    }


    void Speak() {
        printf("CEnglish::Speak(\"Ӣ��\")\r\n");
    }

    virtual void Eat() {
        printf("CEnglish::Eat(����)\r\n");
    }

};

/*
    �麯���ĵ���������
      ��1�������õĺ������麯����
      ��2�������Ǹ����ָ������á�

    �麯�����ã�
       ���о�����������ʱ�����ж�.

    ����������
    ��1����virtual�ؼ��ֵ���Ķ��󣬻��ڶ�����ײ���4���ֽڡ�
    ��2��ͬ�������4���ֽ���ͬ����ͬ������ͬ��
     (3) ��4���ֽڲ����Ǻ���ָ��,�������ָ�롣
    ��4������ŵ��ǵ�ǰ������е��麯���ĵ�ַ��

     ����ã�
       һ��ͨ����ѯ���ļ�ӵ��÷�ʽ��

     ֱ�ӵ��ã�
       ֱ�ӵ��ö�Ӧ�ĺ�����
*/


int main()
{
    srand(time(NULL));

    CPerson per;
    CPerson per1;

    CEnglish eng;
    CEnglish eng1;

    CChinese chs;
    CChinese chs1;

    int nPersonSize = sizeof(CPerson);
    int nEngSize = sizeof(CEnglish);
    int nChsSize = sizeof(CChinese);

    CPerson* ary[2] = {NULL};

    ary[0] = (rand() % 2 == 0) ? (CPerson*)&eng : &chs;
    ary[1] = (rand() % 2 == 0) ? (CPerson*)&eng : &chs;

    CPerson& Ref = eng;


    auto perFoo = &CPerson::Speak;
    auto engFoo = &CEnglish::Speak;
    auto chsFoo = &CChinese::Speak;

    per.Speak();

    //Ref.Speak();

    for (int i = 0; i < 2; i++) {
        ary[i]->Speak();
        //if (ary[i]->m_nType == 1) {
        //    CChinese* pChs = (CChinese*)ary[i];
        //    pChs->Speak();
        //}
        //else if (ary[i]->m_nType == 2) {
        //    CEnglish* pEng = (CEnglish*)ary[i];
        //    pEng->Speak();
        //}

    }

   
   

    return 0;
}

