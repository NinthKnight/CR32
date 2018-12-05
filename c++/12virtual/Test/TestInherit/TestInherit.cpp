// TestInherit.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <ctime>

//面向对象：多态-虚函数
//

class CPerson {
public:
    CPerson() {
        m_nType = 0;
    }

    //虚函数
    virtual void Speak() {
        printf("CPerson::Speak(人话)\r\n");
    }

    virtual void Eat() {
        printf("CPerson::Eat(东西)\r\n");
    }
    
    int m_nType;
};

class CChinese : public CPerson{
public:
    //R"("123")" 原始字符串

    CChinese() {
        m_nType = 1;
    }

    //R"(+Speak("汉语")+)" 原始字符串
    //R"(*CChinese::Speak("汉语")\r\n*)"
    void Speak() {
        printf("CChinese::Speak(\"汉语\")\r\n");
    }

    virtual void Eat() {
        printf("CChinese::Eat(中餐)\r\n");
    }



};

class CEnglish : public CPerson {
public:
    //R"("123")" 原始字符串

    //R"(+Speak("汉语")+)" 原始字符串
    //R"(*CChinese::Speak("汉语")\r\n*)"
    CEnglish() {
        m_nType = 2;
    }


    void Speak() {
        printf("CEnglish::Speak(\"英语\")\r\n");
    }

    virtual void Eat() {
        printf("CEnglish::Eat(西餐)\r\n");
    }

};

/*
    虚函数的调用条件：
      （1）被调用的函数是虚函数。
      （2）对象是父类的指针或引用。

    虚函数调用：
       “感觉”是在运行时做了判断.

    经过分析：
    （1）有virtual关键字的类的对象，会在对象的首部多4个字节。
    （2）同类型这个4个字节相同，不同类型则不同。
     (3) 这4个字节并不是函数指针,而是虚表指针。
    （4）虚表存放的是当前类的所有的虚函数的地址。

     虚调用：
       一种通过查询虚表的间接调用方式。

     直接调用：
       直接调用对应的函数。
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

