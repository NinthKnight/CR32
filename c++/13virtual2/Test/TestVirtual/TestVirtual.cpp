// TestVirtual.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

class CPerson{
public:

    virtual void foo() {
        printf("void CPerson::foo()");
    }

    void foo(int n) {
        printf("void CPerson::foo(int n)");
    }

    virtual void foo(char* p) {
        printf("void CPerson::foo(char* p)");
    }

    virtual void foo(float f) {
        printf("void CPerson::foo(float f)");
    }

};

class CChinese : public CPerson{
public:

    virtual void foo() {
        printf("void CChinese::foo()");
    }

    virtual void foo(int n) {
        printf("void CChinese::foo(int n)");
    }

    void foo(float f) {
        printf("void CChinese::foo(float f)");
    }

    virtual void foo(char* p) {
        printf("void CChinese::foo(char* p)");
    }

};

/*
    �����ߵ��������������ҵ����
       (1) �ڵ����ߵ����У�����ͬ��������
          1�����û�У�������һ����ң�������Ҳ������򱨴�δ���壩
          2������У��򲻻���������ң��ɼ�������ǵ�ǰ�ҵ���ͬ���������ڵ��򣨺������أ�
          
      ��2���ڵ�ǰ�ɼ������У��ҵ���Ѻ��������������ع���
          1�� ���Ψһ����Ѻ��������麯������ô�õ�����ֱ�ӵ��á�
          2�� ���Ψһ����Ѻ������麯��,�жϵ������Ƿ���ָ�������
               1.1) ��������ָ������ã����Ǽ�ӵ��ã��������ǹ���
               1.2�������߲���ָ������ã�����ֱ�ӵ���
             
       ֱ�ӵ���: ˭�����͵�˭
       ��ӵ��ã�˭������˭

*/

int main()
{
    CPerson per;
    CChinese chs;

    CPerson* pPer = &per;
    CPerson* pPer2 = &chs;
    CPerson& perRef = chs;

    CChinese* pChs = &chs;

    per.foo("Hello");
    pPer->foo("Hello");
    pPer2->foo("Hello");
   

    pPer->foo();
    pPer2->foo();
    perRef.foo();

    pPer->foo(2);
    pChs->foo(2);
    pPer2->foo(2);
    perRef.foo(2);

    pPer->foo(2.0f);
    pPer2->foo(2.0f);
    perRef.foo(2.0f);

   
    return 0;
}

