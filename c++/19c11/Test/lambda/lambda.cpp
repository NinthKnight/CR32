// lambda.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

//lambda���ʽ -- ��������
//���ʽ:
//[capture](paras)mutable->return type{statement}
/*
[�����б�](�����б�) mutable(��ѡ) �쳣���� -> �������� {
// ������
}

    int foo(int n1, int n2){
    
    }

    ==��

    [](int n1, int n2)->int{

    }

*/

void foo() {

    int n = 2;
    int m = 3;
    
    //&
    int k = [&](int n1, int n2)mutable->int {

        n++;
        printf("n = %d\r\n", n);
        printf("m = %d\r\n", m);
        return n1 + n2;
    }(1, 2);

    printf("n = %d\r\n", n);
    //printf("k = %d\r\n", k);

    //auto f = [](int n1, int n2)->int {

    //};
    //f(1, 2);


}

int main()
{
    foo();
    return 0;
}

