// overload.cpp : �������̨Ӧ�ó������ڵ㡣
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

//�������أ�
// 1. C++��������ͬ���ĺ��������Ǳ�������һ��������
//    (1)�����б�ͬ�����Ͳ�ͬ, ����������ͬ,˳��ͬ
//    (2)�������Ͳ������ǣ��޷����ؽ��������������ֵĺ���	
//    (3)����Լ���������ǣ�
//    (4)��������ͬ��

//extern "C" {
//
//    int GetMax(int a, int b);
//    //xxxx
//}

// 1. ���ݺ������Ҷ�Ӧ�ĺ�������Ϊ��ѡ������
//    1.1�����ѡ��������Ϊ0����δ��������Ҳ�����ʶ����
// 2. ��ѡ�������� > 0, �Ӻ�ѡ����ƥ��ĺ�������ȫƥ�䣬����ת����ƥ�䣨char <-> int, float <->double float <-> int�ȣ���
//    2.1 ���ƥ��ĺ������� == 0�� �����(��ʽת��ʧ��)
//    2.2 ���ƥ��ĺ������� > 0�������ƥ�䡣
// 3. ���ƥ��ĸ��� = 1, �ͻ���øú���
//    ���ƥ��ĸ��� > 1���ͻᱨ������

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

