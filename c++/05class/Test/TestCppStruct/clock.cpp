#include "stdafx.h"

#include "clock.h"

//函数的定义,需要加上结构体名作用域
int tagClock::SetTime(int nH, int nM, int nS) {
    //this指针表示当前调用该函数的对象的地址
    
    this->nHour = nH;
    nMinute = nM;
    nSecond = nS;

    return 0;
}