#include "stdafx.h"

#include "clock.h"

//�����Ķ���,��Ҫ���Ͻṹ����������
int tagClock::SetTime(int nH, int nM, int nS) {
    //thisָ���ʾ��ǰ���øú����Ķ���ĵ�ַ
    
    this->nHour = nH;
    nMinute = nM;
    nSecond = nS;

    return 0;
}