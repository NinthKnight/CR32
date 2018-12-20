// TestStack.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stack>
#include "MyStack.h"

void foo_stack(int n) {   
    std::stack<int> stk;

    for (int i = 0; i < n; i++) {
        stk.push(i);
    }

    while(!stk.empty()){
    
        printf("%d ", stk.top());
        stk.pop();
    }

    printf("\r\n");
}

void foo_mystack(int n) {
    CMyStack stk;

    for (int i = 0; i < n; i++) {
        stk.push(i);
    }

    while (!stk.empty()) {

        printf("%d ", stk.top());
        stk.pop();
    }

    printf("\r\n");
}

int main(int argc, char* argv[])
{
    int n = argc * 5;
    foo_mystack(n);

    return 0;
}

