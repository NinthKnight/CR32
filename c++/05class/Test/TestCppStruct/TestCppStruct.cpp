// TestCppStruct.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include "clock.h"

//��ͨ�ĺ���ָ��
typedef int(*PFN_SetTime)(int nH, int nM, int nS);

//���еĺ���ָ��
typedef int(__stdcall tagClock::*PFN_SetTimeClass)(int nH, int nM, int nS);


union unFun{
    PFN_SetTime pfn;
    PFN_SetTimeClass pfn_class;
};

//�������ݣ��Ĵ��� ջ
//  thiscall --> ������ĳ�Ա�����ĵ���Լ���� �������ڲ�ʹ��
//  fastcall
//  cdecl
//  stdcall

int main()
{
    tagClock cl1;
    tagClock cl2;
    int nSize = sizeof(tagClock);
    //cl.nHour = 1;

    cl1.SetTime(1, 2, 3);
    cl2.SetTime(4, 5, 6);

    //unFun u;
    PFN_SetTimeClass pfn_class;
    pfn_class = &tagClock::SetTime;


    (cl1.*pfn_class)(1, 2, 3);


    tagClock* pCL = &cl1;
    (pCL->*pfn_class)(1, 2, 3);

    //u.pfn(1, 2, 3);
    //cl.SetTime(1, 2, 3);

    //int* pHour = (int*)&cl;
    //*pHour = 123;

    return 0;
}

