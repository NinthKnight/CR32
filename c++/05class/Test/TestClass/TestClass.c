// TestClass.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

//�������
/*
    1. ��װ
    2. �̳�
    3. ��̬
        //û�ж�̬
        for (int i = 0; i < nCount; i++){
           if (ʿ��[i]== ��ʿ��{
               ��ʿ.��ս��������
           }
           else if ��ʿ��[i]== ��ǹ�֣�{
               ��ǹ��.Զ�̹���()
           }
       }

       //�ж�̬
       for (int i = 0; i < nCount; i++){
            ʿ��[i]->����();
       }


*/

/*
    1. ��װ ����+��Ϊ

*/
//�ӱ�
typedef int(*PFN_SetTime)(struct tagClock* this, int nH, int nM, int nS);
struct tagClock {
    
    //����
    int nHour;
    int nMinute;
    int nSecond;

    PFN_SetTime pfn_set;
};

//��Ϊ
int SetTime(struct tagClock* pClock, int nH, int nM, int nS) {

    pClock->nHour = nH;
    pClock->nMinute = nM;
    pClock->nSecond = nS;

    return 0;
}

int main()
{
    struct tagClock cl;
    cl.nHour = 25;
    cl.nMinute = 50;
    cl.pfn_set = SetTime;
    
    cl.pfn_set(&cl, 1, 2, 3);

    //cl.pfn_set(1, 2, 3);

    return 0;
}

