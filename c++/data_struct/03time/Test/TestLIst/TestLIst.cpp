// TestLIst.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <list>

//����
void foo_list() {
    std::list<int> lt;
    for (int i = 1; i < 4; i++){
        lt.push_back(i);
    }

    for (std::list<int>::iterator it = lt.begin();
         it != lt.end(); it++){
        printf("%d ", *it);
    }

    printf("\r\n");
}

int main()
{
    foo_list();

    return 0;
}

