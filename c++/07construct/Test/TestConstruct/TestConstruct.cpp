// TestConstruct.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "TestB.h"
#include <memory>

class CTest {
public:

    //构造函数:
    //1. 由编译器在合适的时机调用
    //2. 用于初始化对象的成员
    //3. 构造函数不允许定义返回值
    //4. 构造函数可以有参数,支持默认参
    //   1)仅有一个参数时 ,该函数既表示构造函数，又表示一种隐式转换
    //     从而支持：CTest obj = 1，可以使用关键字explicit表示只支持
    //     显示调用构造函数，不允许隐式转换。
    //   2)支持函数重载
    //   3)如果不重载构造函数，编译器会提供一个无参的默认构造函数
    //     CTest() = default 表示使用默认的构造函数。
    //     CTest() = delete 表示禁止使用某函数（删除）。
    // 5. 构造函数可以使用初始化列表来初始化成员：
    //     CTest(int n, int k)
    //          :m_n(n), m_k(k)
    // 6. 构造函数通常不要手动调用( t1.CTest::CTest(2, 3);)

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

    //析构函数
    // 1.用于资源的反初始化
    // 2.编译器在合适的时机调用（对象不在使用）
    // 3.析构函数不能有参数和返回值,不能重载
    
    //构造函数和析构函数通常是公有

    ~CTest() {
    
        m_testB.foo();
        std::cout << "~CTest()" << std::endl;
        m_n = 1;
        m_k = 2;
        pszName = nullptr;
    }

    //调用时机
    //1. 局部对象
    //  构造时机： 在定义时调用构造函数
    //  析构时机： 在出作用域时调用析构函数
  
    //2. 全局对象 与程序“同生共死”
    //  构造时机 ： main()之前
    //  析构时机 ： main()之后

    //3. 堆对象
    //  构造时机：调用new，分配空间后
    //  析构时机：调用delete,释放空间前

    //4. 类（CTestA）的成员对象(CTestB)
    //  构造时机：在CTestA的构造函数中，先朋友(成员对象CTestB)，后自己CTestA
    //  析构时机：在CTestA的析构函数中先自己CTestA，后朋友（成员对象CTestB）
    //  如果朋友类CTestB有参数，那么必须在CTestA的初始化列表中说明参数调用其对应的构造函数

    //运算符（+ = - ）：new 
    // CTest* pTest = new CTest(1, 2);
    // 1. 申请堆空间
    // 2. 调用构造

    // delete:
    // delete pTest;
    // 1. 先调用析构函数
    // 2. 再释放空间

    // new 与 delete匹配使用
    // new[] 与delete[]匹配使用，
    // 当new[]对象数组时，必须使用delete[]


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

    //智能指针
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

