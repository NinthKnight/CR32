// TestClass.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

//面向对象
/*
    1. 封装
    2. 继承
    3. 多态
        //没有多态
        for (int i = 0; i < nCount; i++){
           if (士兵[i]== 骑士）{
               骑士.近战攻击（）
           }
           else if （士兵[i]== 火枪手）{
               火枪手.远程攻击()
           }
       }

       //有多态
       for (int i = 0; i < nCount; i++){
            士兵[i]->攻击();
       }


*/

/*
    1. 封装 数据+行为

*/
//钟表
typedef int(*PFN_SetTime)(struct tagClock* this, int nH, int nM, int nS);
struct tagClock {
    
    //数据
    int nHour;
    int nMinute;
    int nSecond;

    PFN_SetTime pfn_set;
};

//行为
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

