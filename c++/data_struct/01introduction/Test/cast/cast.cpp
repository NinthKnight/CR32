// cast.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

//cast ת��
//1. const_cast
//   ����ȥ�����������const���Ի�volatility

//2. static_cast
//   (1) �ȼ���C�е���ʽת��
//   (2) û������ʱ���ͼ������֤ת���İ�ȫ��

//3. dynamic_cast
//   (1) �����������ֱ�ӵ�ת��
//   (2) �������Ҫ���麯��
//  ��3���ṩ����ʱ���ͼ��

//4. reinterpret_cast
//   �ȼ���ǿת 


class CFather {
public:
    virtual void test() {
    }
};

class CSon : public CFather{
public:

};

void foo_dynamic() {
    CFather fa;
    CSon son;

    CFather* pFather = dynamic_cast<CFather*>(&son);
    CSon* pSon = dynamic_cast<CSon*>(&fa);
    CSon* pSon2 = dynamic_cast<CSon*>(pFather);
    CSon* pSon3 = static_cast<CSon*>(&fa);
    


}


void foo_static() {
    int n = 1;
    float f = (float)n;



    //float f2 = static_cast<float>(n);
    ////int f3 = static_cast<int>(&n);
    //int f4 = reinterpret_cast<int>(&n);
    //int f5 = (int)(&n);
    //float f6 = f4;


}

int main()
{
    foo_dynamic();

    //volatile int n;
    return 0;
}

