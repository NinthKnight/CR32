// TestThread.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <thread>
#include <iostream>
#include <functional>
using namespace std;

class CMyClass {
public:
    void foo(int a, int b) {
        printf("a + b = %d\r\n", a + b);
    }


};


int main()
{
    CMyClass obj;
    //obj.foo(1, 2);

    //thread t;

    //t = thread([&](thread* pT) {
    //    std::thread::id t1_id =std::this_thread::get_id();
    //    //std::thread::id id = pT->get_id();

    //    cout << "t1's id: " << t1_id << endl;

    //}, &t);

    //printf("main: %d\r\n", std::thread::id());

    //t.join();
    //function<void(int a, int b)> f = std::bind(&CMyClass::foo,
    //    &obj,
    //    std::placeholders::_1,
    //    std::placeholders::_2);
    //
    //thread test(f, 1, 2);

    thread t2;
    t2 = thread(&CMyClass::foo, &obj, 1, 2);


    t2.join();

    return 0;
}

//#include <iostream>
//#include <thread>
//#include <chrono>
//
//void foo()
//{
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//}
//
//int main()
//{
//    std::thread t1(foo);
//    std::thread::id t1_id = t1.get_id();
//
//    std::thread t2(foo);
//    std::thread::id t2_id = t2.get_id();
//
//    std::cout << "t1's id: " << t1_id << '\n';
//    std::cout << "t2's id: " << t2_id << '\n';
//
//    t1.join();
//    t2.join();
//}

