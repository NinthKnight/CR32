// ref.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

//��ֵ����
//1. �����������Ĺ�����Ӧ�Ĵ洢����ַ����ָ��
//2. ����һ����ʼ���󣬲��ܸı����õĹ�ϵ
//3. ���ñ��븳��ֵ,����ΪNULL����,Ӧ����һ������
//4. �������ÿ����ó�����ʼ��
//5. ʹ�ó���

//int* foo() {
//    int n = 1;
//    return &n;
//}

//int foo2(int* p) {
//    char szBuf[256] = { 0 };
//    *p = 123;
//
//}

void exchange(int*& n1, int*& n2) {
    int* k = n1;
    n1 = n2;
    n2 = k;
    return;
}

int& foo_ref() {
    int n = 1;
    return n;
}

int main()
{
    int m = 1;
    int n = 2;

    int* pM = &m;
    int* pN = &n;

    exchange(pM, pN);

    //int& nRef = foo_ref();
    //
    //nRef = 3;

    //foo2(pN);


    return 0;


    //int n = 0;
    //int m = 2;
    ////int* pN = &n;
    ////*pN = 1;
    //const int& refN = 1000; //����
    

                      
    //refN = m;
    //refN = 1;


    return 0;
}

