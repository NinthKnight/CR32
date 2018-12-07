// TestInherit.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <string>
#include <iostream>

//������󣺼̳�
//
namespace CR32{
    void foo() {
        printf("CR32: void foo()\r\n");
    }
}

void foo() {
    printf("global: void foo()\r\n");
}

float n = 3;

class CPerson {
public:
    CPerson(){
        n = 3;
    }

    void foo(char* p) {
        printf("void CPerson::foo(char* p)\r\n");
    }

    int n;
};

class CTeacher: public CPerson {
public:
    CTeacher(): CPerson()
    {
    }

    void foo(int n) {
        printf("void CTeacher::foo(int n)\r\n");
    }

    void test() {
        //foo();
        CPerson::n = 1;
        ::n = 3.0f;
    }

    char* n;
private:
};

/*
    �������أ�
        ��1�� ͬ����
        ��2�� ������ͬ
         (3)  ���Ͳ�����
 
    �������أ�
         (1) ͬ��
        ��2) ����������ֵ������Լ����������
        ��3��������ͬ

        ����������ң�һ���ҵ�ͬ�����������ⲿ���������ء� �ڲ��پ����������صĹ���ƥ�䡣
*/
int main()
{
    CTeacher t;
    //t.foo();
    t.test();
    

    return 0;
}

