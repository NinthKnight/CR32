// MyVector.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <vector>
#include <algorithm>    // std::for_each
#include "MVector.h"

//��̬����

void myfunction(int n) {  
    printf("%d ", n);
}

void foo_std() {

    std::vector<int> v;
  
    //v.resize(10);

    //����
    v.push_back(1);
    v.push_back(2);

    auto itBegin = v.begin();
    
    v.insert(v.begin(), 3);

    for (auto n : v) {
        printf("%d ", n);
    }
    printf("\r\n");

    //printf("%d", *itBegin);


    //����
    //��ȡ�׸�Ԫ�ص�λ�ã�����ֵ�ǵ���������
    //�������Ƕ�Ԫ�ص�λ�õķ�װ���ڲ���
    //auto it = v.begin();

    std::vector<int>::iterator it = v.begin();
    it += 1;
    v.insert(it, 0);

    v.erase(it);

    //ɾ
    v.pop_back();

    //��
    v[0] = 100;

    //����
    for (int i = 0; i < v.size(); i++) {
        printf("%d ", v[i]);
    }
    printf("\r\n");

    for (auto it = v.begin(); it != v.end(); it++) {
        printf("%d ", *it);
    }
    printf("\r\n");

    for (auto n : v) {
        printf("%d ", n);
    }
    printf("\r\n");

    std::for_each(v.begin(), v.end(), myfunction);
    printf("\r\n");

    std::for_each(v.begin(), v.end(), [=](int n)->void {
        printf("%d ", n);
    });

    printf("\r\n");
}

void foo_my() {
    CMyVector v;
    for (int i = 0; i < 10; i++) {
        v.push_back(i);
    }
   
    auto beginIt = v.begin();

    v.insert(beginIt, 100);

 

    for (beginIt = v.begin(); beginIt != v.end(); beginIt++) {
        printf("%d ", *beginIt);
    }
    printf("\r\n");

    //for (int i = 0; i < v.size(); i++) {
    //    printf("%d ", v[i]);
    //}

    //printf("\r\n");
}


int main()
{
    foo_my();


    return 0;
}

