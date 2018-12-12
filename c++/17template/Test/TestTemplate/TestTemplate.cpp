// TestTemplate.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
//模板
// template
// 1. 函数模板
// 2. 类模板

//int GetMax(int a, int b) {
//    return a > b ? a : b;
//}

//double GetMax(double a, double b) {
//    return a > b ? a : b;
//}

//函数模板
template<typename T>
T GetMax(T a, T b) {
    //1asdfsadfsadf;
    return a > b ? a : b;
}


template<typename T = int, int SIZE = 100>
T Test(T a, T b) {
    //1asdfsadfsadf;
    int n = SIZE;
    return a > b ? a : b;
}
//const char* GetMax(const char* a, const char* b) {
//    //1asdfsadfsadf;
//    int nA = strlen(a);
//    int nB = strlen(b);
//    return nA > nB ? a : b;
//}

//模板特例
template<>
const char* GetMax(const char* a, const char* b) {
    //1asdfsadfsadf;
    int nA = strlen(a);
    int nB = strlen(b);
    return nA > nB ? a : b;
}

//int test(int a, float f) {
//    return a;
//}
//
//float test(int a, float f) {
//    return a;
//}

//template<typename T1, typename T2>
//T1 GetMax(T1 a, T2 b) {
//    return a;
//}

int main()
{
    Test(1, 2);

    //隐式实例化模板
    //int n = GetMax(1.0f, 2.0f);
    //int n = GetMax(1, 2.0f); 二义性

    //显式实例化模板
    //n = GetMax<int>(1, 2.0f);
    const char* p = GetMax("abc", "1234");
    //GetMax<int, float>(1, 2.0f);

    //模板特例/特化

    return 0;
}

