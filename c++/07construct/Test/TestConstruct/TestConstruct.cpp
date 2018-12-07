// TestConstruct.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include "TestB.h"
#include <memory>

class CTest {
public:

    //���캯��:
    //1. �ɱ������ں��ʵ�ʱ������
    //2. ���ڳ�ʼ������ĳ�Ա
    //3. ���캯���������巵��ֵ
    //4. ���캯�������в���,֧��Ĭ�ϲ�
    //   1)����һ������ʱ ,�ú����ȱ�ʾ���캯�����ֱ�ʾһ����ʽת��
    //     �Ӷ�֧�֣�CTest obj = 1������ʹ�ùؼ���explicit��ʾֻ֧��
    //     ��ʾ���ù��캯������������ʽת����
    //   2)֧�ֺ�������
    //   3)��������ع��캯�������������ṩһ���޲ε�Ĭ�Ϲ��캯��
    //     CTest() = default ��ʾʹ��Ĭ�ϵĹ��캯����
    //     CTest() = delete ��ʾ��ֹʹ��ĳ������ɾ������
    // 5. ���캯������ʹ�ó�ʼ���б�����ʼ����Ա��
    //     CTest(int n, int k)
    //          :m_n(n), m_k(k)
    // 6. ���캯��ͨ����Ҫ�ֶ�����( t1.CTest::CTest(2, 3);)

    //explicit CTest(int n, int k = 1) {
    //    std::cout << "CTest(int n, int k) :" << n << std::endl;

    //    //Init(n);
    //}

    //explicit CTest(int n) {
    //    std::cout << "CTest(int n) :" << n << std::endl;

    //    //Init(n);
    //}

    CTest() {
        std::cout << "CTest()" << std::endl;
    }

    explicit CTest(int n) {
        std::cout << "CTest(int n)" << n << std::endl;
    }


    CTest(int n, int k) 
        :m_n(n), m_k(k),m_testB(1)
    {
        std::cout << "CTest(int n, int k)  :" << n << std::endl;
        m_n = 11;
        m_k = 22;

        pszName = (char*)malloc(10);
    
    }

    //void foo() = delete;

    void Init(int n) {
        //foo();
        m_n = n;
    }

    void Release() {
        free(pszName);
    }

    //��������
    // 1.������Դ�ķ���ʼ��
    // 2.�������ں��ʵ�ʱ�����ã�������ʹ�ã�
    // 3.�������������в����ͷ���ֵ,��������
    
    //���캯������������ͨ���ǹ���

    ~CTest() {
    
        m_testB.foo();
        std::cout << "~CTest()" << std::endl;
        m_n = 1;
        m_k = 2;
        pszName = nullptr;
    }

    //����ʱ��
    //1. �ֲ�����
    //  ����ʱ���� �ڶ���ʱ���ù��캯��
    //  ����ʱ���� �ڳ�������ʱ������������
  
    //2. ȫ�ֶ��� �����ͬ��������
    //  ����ʱ�� �� main()֮ǰ
    //  ����ʱ�� �� main()֮��

    //3. �Ѷ���
    //  ����ʱ��������new������ռ��
    //  ����ʱ��������delete,�ͷſռ�ǰ

    //4. �ࣨCTestA���ĳ�Ա����(CTestB)
    //  ����ʱ������CTestA�Ĺ��캯���У�������(��Ա����CTestB)�����Լ�CTestA
    //  ����ʱ������CTestA���������������Լ�CTestA�������ѣ���Ա����CTestB��
    //  ���������CTestB�в�������ô������CTestA�ĳ�ʼ���б���˵�������������Ӧ�Ĺ��캯��

    //�������+ = - ����new 
    // CTest* pTest = new CTest(1, 2);
    // 1. ����ѿռ�
    // 2. ���ù���

    // delete:
    // delete pTest;
    // 1. �ȵ�����������
    // 2. ���ͷſռ�

    // new �� deleteƥ��ʹ��
    // new[] ��delete[]ƥ��ʹ�ã�
    // ��new[]��������ʱ������ʹ��delete[]


private:
    int m_n;
    int m_k;
    char* pszName;

    CTestB m_testB;

};



class CApplication {
private:
    char* m_name;
    int m_argc;
    char* m_argv[];

};

CApplication g_App;

//CTest t1(1, 2);
int n = 3;

int main()
{
    //t1.Init();
  
    //CTest t = 1;
    //CTest t2(2);
    //CTest t3 = CTest(3);

    //int* pN = (int*)malloc(sizeof(int));
    //CTest* pTest = (CTest*)malloc(sizeof(CTest));
    //int* pN = new int(1);

    //int* pAry = new int[5];

    //pAry[0] = 1;

    //int n = 3;
    //delete [] pAry;

    //CTest* pTest = new CTest[3];

    //����ָ��
    {
        CTest t;
        //std::shared_ptr<int> pInt(new int);
        //std::shared_ptr<CTest> pTest = std::shared_ptr<CTest>(new CTest);
        //*pInt = 1;


        //pTest->Init(1);
    }


    //std::shared_ptr<CTestB> pTestB(new CTestB);

    //auto pTest = std::shared_ptr<CTest>(new CTest);

    //std::shared_ptr<CTestB> pTestB = new CTestB;

    //delete[] pTest;
    //delete (CTest*)((char*)pTest - 4);

    //t1.CTest::CTest(2, 3);
    //t1.foo();
    //CTest t2(1, 2);
    //CTest t;

    //t1.Release();

    //CTest t = 1;
    //double dbl = 3.14f;
    //int n = dbl;

    //CTest t(1);

    //t.Init(1);


    return 0;
}

