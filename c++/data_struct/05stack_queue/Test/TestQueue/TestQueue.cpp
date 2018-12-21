// TestQueue.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <queue>

void foo_queue() {

    std::queue<int> que;

    for (int i = 0; i < 10; i++) {
        que.push(i);
    }

    while (!que.empty()) {
        
        printf("%d ", que.back());
        que.pop();
    }

    printf("\r\n");

}



int main()
{
    foo_queue();
    return 0;
}

