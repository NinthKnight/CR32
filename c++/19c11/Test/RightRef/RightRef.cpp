// RightRef.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <memory>

//����
//��ֵ����
//   1.�������������ʽ
//   2.����ֵ

class CTest {
public:
    CTest() {
        printf("CTest()\r\n");
    }

    CTest(CTest& obj) {
        printf("CTest(&obj)\r\n");
        //���
        //memcpy(m_pBuf, obj.m_pBuf, nLength);



    }

    //�ƶ�����
    CTest(CTest&& obj) {
        printf("CTest(&&obj)\r\n");

        //"͵"��Դ
        m_pBuf = obj.m_pBuf;
        obj.m_pBuf = nullptr;


    }

    

    ~CTest() {
        printf("~CTest()\r\n");
    }

private:
    char* m_pBuf;

};

CTest foo() {
    CTest t;

    return t;
}

void foo2(CTest&& t) {


}


int main()
{
    CTest t;

    foo2(std::move(t));
    foo2((CTest&&)t);

    //CTest t1 = foo();


    //int n;
    //n = 1;

    //��ֵ����
    //int& ref = n;
    //ref = 1123;

    ////��ֵ����
    //int&& ref2 = 1;
    //ref2 = 3;

    return 0;
}

