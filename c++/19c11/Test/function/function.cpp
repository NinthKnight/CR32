// function.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <functional>

//C11�пɵ��ö���
//1. ��ͨ����
//2. ���Ա����
//3. �º���
//4. lambda���ʽ

class Functor {
public:
    int operator()(int n) {
        m_n = n;
        return n;
    }

    int test() {
        return m_n;
    }

    int m_n;
};

int test(int n1, int n2) {

    return n1 + n2;
}

//bind

int main()
{
    Functor obj;
    int n = obj(1);

    auto foo = obj(1);

    std::function<int(int, int)> f2 = [&](int n1, int n2)mutable->int {

        return n1 + n2;
    };

    f2(1, 2);

    std::function<int(int, int)> f3 = test;
    f3(1, 2);

    std::function<int(Functor*)> f4 = &Functor::test;
    f4(&obj);


    return 0;
}

