// TestLIst.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <list>
#include "MyList.h"

//链表
void foo_list() {
    std::list<int> lt;
    for (int i = 1; i < 2; i++){
        lt.push_back(i);
    }

    std::list<int>::iterator it = lt.begin();

    //it++;
    //it++;

    for (std::list<int>::iterator it = lt.begin();
         it != lt.end(); it++){
        printf("%d ", *it);
    }

    printf("\r\n");
}

void foo_mylist() {
    CMyList lt;
    for (int i = 0; i < 3; i++) {
        lt.push_back(i);
    }

    lt.reverse();

    for (CMyList::Iterator it = lt.begin();
    it != lt.end(); it++) {
        printf("%d ", *it);
    }

    printf("\r\n");
}


//a b c d c b a

int main()
{
    foo_mylist();

    return 0;
}

