// work2_20181128.cpp: 定义控制台应用程序的入口点。
//举例说明关键字=default,=delete在类中的作用。

#include "stdafx.h"
#include <iostream>
class CTest {
public:
    //CTest() = default; //表示使用默认的构造函数。
    CTest() = delete;// 表示禁止使用某函数（删除）。

    void foo() {
        printf("123\r\n");
    }

private:
    int m_n;
};

//CTest t() {
//    int n = 3;
//    return nu
//}

int main()
{
    //CTest t;//当使用关键字default时，可行
    //CTest t;//当使用关键字delete并且没有添加新的函数时，不可行
//当使用关键字delete并且没有添加新的函数时，加括号后可行
              /*
              猜想：当使用关键字delete并且没有任何手动添加构造函数时，类自动生成一个新的无参构造函数
              (因为类不可以没有构造或析构函数)，但不是默认的，所以可以调用而不报错
              */
    CTest t();
    t();

    //t.foo();

    return 0;
}

