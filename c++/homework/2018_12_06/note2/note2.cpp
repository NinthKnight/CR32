#include <iostream>
class CPerson {
public:
    virtual void foo()
    {
        printf("void CPerson::foo()\r\n");
    }

    void foo(int n) 
    {
        printf("void CPerson::foo(int n)\r\n");
    }

    virtual void foo(char* p)
    {
        printf("void CPerson::foo(char* p)\r\n");
    }

    virtual void foo(float f) 
    {
        printf("void CPerson::foo(float f)\r\n");
    }

};

class CChinese : public CPerson {
public:
    virtual void foo() {
        printf("void CChinese::foo()\r\n");
    }

    virtual void foo(int n) {
        printf("void CChinese::foo(int n)\r\n");
    }

    void foo(float f) {
        printf("void CChinese::foo(float f)\r\n");
    }

    virtual void foo(char* p) {
        printf("void CChinese::foo(char* p)\r\n");
    }
};

int main()
{
    CPerson per;
    CChinese chs;

    CPerson* pPer = &per;
    CPerson* pPer2 = &chs;
    CPerson& perRef = chs;

    CChinese* pChs = &chs;

    per.foo(const_cast<char*>("Hello"));
    pPer->foo(const_cast<char*>("Hello"));
    pPer2->foo(const_cast<char*>("Hello"));

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