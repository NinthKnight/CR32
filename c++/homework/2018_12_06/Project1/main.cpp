/*试预测并说明程序执行结果,并以此为基础总结覆盖、隐藏、重载的区别（触发条件的区别、实现原理的区别）*/


#include <stdlib.h>
#include <iostream>
using namespace std;
class Base
{
public:
    virtual void Handle1(float x)
    {
        cout << "Base::Handle1(float) " << x << endl;
    }
    void Handle2(float x)
    {
        cout << "Base::Handle2(float) " << x << endl;
    }
    void Handle3(float x)
    {
        cout << "Base::Handle3(float) " << x << endl;
    }
};

class Derived : public Base
{
public:
    virtual void Handle1(float x)
    {
        cout << "Derived::Handle1(float) " << x << endl;
    }
    void Handle2(int x)
    {
        cout << "Derived::Handle2(int) " << x << endl;
    }
    void Handle3(float x)
    {
        cout << "Derived::Handle3(float) " << x << endl;
    }
    void Handle3(double x)
    {
        cout << "Derived::Handle3(double) " << x << endl;
    }
};
/* 观察以上类声明及实现，试预测以下main中的执行结果。
注意两点：
1. 调用的方法是哪个
2. 调用造成的原因，是重载、覆盖、隐藏中的哪一种？
*/
void main(void)
{
    Derived DervObj;
    Base *pBase = &DervObj;
    Derived *pDerv = &DervObj;

    pBase->Handle1(3.14f);
    //类型 Base*
    //Base类 有最佳匹配函数
    //virtual void Handle1(float x);
    //指针，间接调用
    //保存的是DervObj的虚表。调用的是Derived的virtual void Handle1(float x)


    pDerv->Handle1(3.14f);
    //pDerv类型：Derived
    //Derived有最佳匹配的函数：virtual void Handle1(float x)
    //虚函数。指针，间接调用
    //保存的是Derived的虚表。调用的是Derived的virtual void Handle1(float x)

    cout << endl;

    pBase->Handle2(3.14f);
    //pBase类型：Base*
    //Base类中有最佳匹配的函数：
    //不是虚函数。直接调用Base：：void Handle2(float x)


    pDerv->Handle2(3.14f);
    //pDerv类型：Derived *  
    //类Derived 有最佳匹配：void Handle2(int x)
    //不是虚函数。直接调用Derived：：void Handle2(float x)

    cout << endl;

    pBase->Handle3(3.14f);
    //pBase类型：Base *
    //Base类有最佳匹配函数 void Handle3(float x)
    //不是虚函数：Base：：void Handle3(float x)
    //

    pDerv->Handle3(3.14f);
    //pDerv类型：Derived*
    //Derived类有最佳匹配函数 void Handle3(float x)
    //不是虚函数：Derived：：void Handle3(float x)

    pDerv->Handle3(3.14);
    //pDerv类型：Derived *
    //Derived类有最佳匹配函数 void Handle3(double x)
    //不是虚函数：Derived：：void Handle3(double x)

    cout << endl;

    pDerv->Handle3(3);
    //pDerv类型：Derived*
    //Derived类有匹配函数  void Handle3(float x)
    //                   void Handle3(double x)
    //                   二义性；
}