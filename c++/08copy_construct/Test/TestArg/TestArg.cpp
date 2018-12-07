// TestArg.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

class CTest {
public:
    CTest(int n = 1) 
        :m_nTest(n)
    {
        printf("CTest()\r\n");
    }

    CTest(CTest& obj)
    {
        printf("CTest(CTest& obj)\r\n");
        m_nTest = obj.m_nTest;
    }

    CTest operator=(CTest& obj) {
        printf("operator=(CTest& obj)\r\n");
        m_nTest = obj.m_nTest;
        return *this;
    }

    ~CTest() {
        printf("~CTest()\r\n");
    }

    //����Ա����
    void foo_test()  const {
        //m_nTest = 1;
        //this->m_nTest = 1;
        CTest* p = const_cast<CTest*>(this);
        p->m_nTest = 1;
        //this = &m_nTest;
        //m_n_mutable_Test = 2;
        printf("m_nTest = %d\r\n", m_nTest);
    }

    void foo_test1(){
        //m_nTest = 1;
        //this->m_nTest = 1;
      
        //this = &m_nTest;
        //m_n_mutable_Test = 2;
        printf("m_nTest = %d\r\n", m_nTest);
    }

private: 
    mutable int m_n_mutable_Test;
    int m_nTest;
};

//const ����Ա������
// 1. �ú����ڲ������޸���ĳ�Ա����(����mutable��������ĳ�Ա����)
// 2. ԭ������Ϊ����Ա�����е�thisָ���������const T* const;
// 3. ��ͨ�ĳ�Ա������thisָ���������T* const;


//������Ϊ����
//1. �βλ´���������: void foo_arg(CTest tArg)
//2. ͨ�������Ĵ��ݻ�ʹ������(const ����)�� void foo_argRef(const CTest& tRefArg)��

void foo_arg(CTest tArg) {
    tArg.foo_test();
}

void foo_argRef(const CTest& tRefArg) {
    tRefArg.foo_test();
}

void foo(int nArg) {
    nArg = 2;
}

//������Ϊ����ֵ��Ҳ���п�������
// 1. ����ⲿû�н��ܺ����Ķ��󣬸÷��صĶ����Ǹ��������󣬵��������еġ�;��ʱ��������
//    foo_rtn().foo_test() , printf("123\r\n");printf("456\r\n");
//    123
//    ~CTest() -->˵������������
//    456
    


CTest foo_rtn() {
    //CTest t(1);

    return 1;
}

//��������
// CTest(1);
int main()
{
    //foo_rtn().foo_test() , printf("123\r\n");
    //printf("456\r\n");
    CTest t = foo_rtn();

    //int n = 1;
    //foo(n);

    //CTest t = 1;

    //CTest t;
    //foo_arg(1);
    //foo_arg(CTest(1));
    
    //foo_argRef(t);

    return 0;
}

