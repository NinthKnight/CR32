// inline.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include "test.h"
//��������
// 1. inline�ǶԱ������Ľ���
// 2. debug�汾û��inline��Ϊ�˷������
// 3. ������������д��ͷ�ļ���

#define GETMAX(a, b) ((a) > (b) ? (a) : (b))

int main(int argc, char* argv[])
{
    foo();
    getMax(1, 2);

    //int n = argc;
    //int k = getMax(++n, 1);

    //printf("%d", k);
    //int k = a > b ? a : b;
    //GETMAX(++n, 1);

    //((++n) > (1) ? (++n) : (1))

    return 0;
}

