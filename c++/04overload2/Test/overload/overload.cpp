// overload.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

//
//int GetMaxInt(int a, int b) {
//    return a > b ? a : b;
//}
//
//float GetMaxFloat(float a, float b) {
//    return a > b ? a : b;
//}
//
//#define GETMAX(type) type GETMAX##type(type a, type b)

//GETMAX(int)
//int GETMAXint(int a, int b)

//函数重载：
// 1. C++中允许定义同名的函数，但是必须满足一定条件：
//    (1)参数列表不同：类型不同, 参数个数不同,顺序不同
//    (2)返回类型不做考虑：无法重载仅按返回类型区分的函数	
//    (3)调用约定不做考虑：
//    (4)作用域相同：

//extern "C" {
//
//    int GetMax(int a, int b);
//    //xxxx
//}

// 1. 根据函数名找对应的函数，作为候选函数。
//    1.1如果候选函数个数为0，则报未定义错误（找不到标识符）
// 2. 候选函数个数 > 0, 从候选中找匹配的函数（完全匹配，可以转换的匹配（char <-> int, float <->double float <-> int等））
//    2.1 如果匹配的函数个数 == 0， 则错误(隐式转换失败)
//    2.2 如果匹配的函数个数 > 0，找最佳匹配。
// 3. 最佳匹配的个数 = 1, 就会调用该函数
//    最佳匹配的个数 > 1，就会报二义性

namespace CR31 {
    int GetMax(float a, int b) {
        return 0;
    }
}
//using namespace CR31;

int GetMax(char ch) {
    return 0;
}
//
//int GetMax(char* psz) {
//    return 0;
//}

//int GetMax(float f) {
//    return 0;
//}

int GetMax(int a) {
    return 0;
}

int GetMax(int a, int b = 0) {
    return 0;
}


//extern "C" int GetMax(int a, float b) {
//    return 0;
//}


int main()
{
    //int c = GetMax(1, 2);

    GetMax(3);

    return 0;
}

