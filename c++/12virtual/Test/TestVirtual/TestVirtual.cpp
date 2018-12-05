// TestVirtual.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Person.h"
#include "Chinese.h"

int main()
{
    CPerson per;
    int nSize = sizeof(per);
    
    CChinese chs;
    int nSize2 = sizeof(chs);


    CPerson* ary[2] = { &per, &chs};

    for (int i = 0; i < 2; i++) {
        //ary[i]->Speak();

        //void* pFoo = ary[i]->m_pVirTable;
        //PFN_VIRTUAL pfn = *((PFN_VIRTUAL*)pFoo+1);
        //(ary[i]->*pfn)();

        (ary[i]->*(*((PFN_VIRTUAL*)ary[i]->m_pVirTable + 1)))();
    }


    //PFN_VIRTUAL pfn = &CPerson::Speak;

    //(per.*pfn)();



    //模仿虚调用，调用Speak
    //(per.*(PFN_VIRTUAL)(per.m_pVirTable[0])();


    return 0;
}

