#pragma once
#include "MyList.h"

class CMyStack : protected CMyList
{
public:
    CMyStack();
    ~CMyStack();

    int size() {
        return CMyList::size();
    }

    bool empty() {
        return CMyList::empty();
    }

    void push(int n) {
        push_back(n);
    }

    void pop() {
        pop_back();
    }

    int top() {
        return back();
    }

};

