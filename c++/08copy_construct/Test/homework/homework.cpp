// work2_20181128.cpp: �������̨Ӧ�ó������ڵ㡣
//����˵���ؼ���=default,=delete�����е����á�

#include "stdafx.h"
#include <iostream>
class CTest {
public:
    //CTest() = default; //��ʾʹ��Ĭ�ϵĹ��캯����
    CTest() = delete;// ��ʾ��ֹʹ��ĳ������ɾ������

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
    //CTest t;//��ʹ�ùؼ���defaultʱ������
    //CTest t;//��ʹ�ùؼ���delete����û������µĺ���ʱ��������
//��ʹ�ùؼ���delete����û������µĺ���ʱ�������ź����
              /*
              ���룺��ʹ�ùؼ���delete����û���κ��ֶ���ӹ��캯��ʱ�����Զ�����һ���µ��޲ι��캯��
              (��Ϊ�಻����û�й������������)��������Ĭ�ϵģ����Կ��Ե��ö�������
              */
    CTest t();
    t();

    //t.foo();

    return 0;
}

