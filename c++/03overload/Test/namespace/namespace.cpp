// namespace.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "test.h"

//using namespace CR32;

//#define CR32 c;

namespace c = CR32;

namespace CR32 {

    namespace test {
        int n = 3;
    }

    int n = 32;
    struct tagTest {
        int nTest;
    };

    void foo() {
        printf("namespace CR32 foo");
    }

}

//using CR32::n;
//using namespace CR32;
/*
  C++������
  1. ȫ����������ռ���
  2. �ֲ������򡢿�������
  3. ���� class

*/

/*
    ��������
    1. �ڲ�ͬ����������Զ�������ͬ���ֵı���
    2. �ڷ��ʵ�ʱ�򣬴���������ң���������->������->ȫ��������    
*/

/*
   namespace ���ֿռ䡢�����ռ�
   1. ͬһ�����ֿռ�����ڲ�ͬ��cpp�в�д��ʵ������ͬһ���ռ���
   2. ���ֿռ����Ƕ��
   3. �������ֿռ�ķ�����
      (1) ʹ�����ֿռ�::���������� CR32::n (�����÷�)
      (2) �������ֿռ� using namespace CR32;
      (3) ����ֻʹ�����ֿռ�Ĳ��ֱ������� using CR32::n;

   4. ���ֿռ�ȡ������ namespace c=CR32; 
   5. using�����Գ������κο��������ĵط�����������ȫ��������ԣ����൱��
      ��Ӧ�Ĵ�����ָ��������λ��չ��
*/

void foo() {
    printf("global foo");
}


int CR32_n = 1;
//int n = -1;
int main()
{
    //int n = 0;
    {
        //int n = 1;
        using CR32::n;
        c::foo();
        printf("%d\r\n", n);
    }
    
    //printf("%d\r\n", n);

    return 0;
}

