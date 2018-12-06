0.  运行并调试 下面的代码。
试预测并说明程序执行结果,并以此为基础总结覆盖、隐藏、重载的区别（触发条件的区别、实现原理的区别）

```
#include "StdAfx.h"
#include <stdlib.h>
#include <iostream.h>

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
    Base *pBase = &DervObj; Derived *pDerv = &DervObj;

    pBase->Handle1(3.14f);   
    pDerv->Handle1(3.14f);
    cout << endl;

    pBase->Handle2(3.14f);   
    pDerv->Handle2(3.14f);
    cout << endl;

    pBase->Handle3(3.14f);   
    pDerv->Handle3(3.14f);
    pDerv->Handle3(3.14);
    cout << endl;

    pDerv->Handle3(3);
}
```
0. 在昨天的题目1中，使得draw()是纯虚函数。尝试创建一个类型为Shape的对象。并试着在构造函数内调用这个纯虚函数，看看结果如何。保留它的纯虚性，对draw()进行定义。

1. 举例说明构造函数和析构函数中调用虚函数是否是虚调用，为什么？

2. 举例说明为什么析构函数通常都是虚函数？

3. 写一个员工类,其中有发薪水的方法。写一个项目经理类，他继承自员工类。写一个程序员类，也继承自员工类。请实现并表现出他们发薪水的多态性

4. 请为主板类制定好接口，使得它可以兼容符合此标准接口的声卡，网卡，显卡等(都用类实现，相应的接口即为函数统一标准即为统一函数)。

5. 将学员录入程序中的学生和老师加入多态性，以适应不同的学生(学生都有说话成员函数可能有的学生是聋哑生，他们的说话方法即为手语)和老师的多态性(老师分为老教师和新教师，老教师都用正常教学，新教师喜欢用多媒体教学，老师有教学这个成员方法)

6. 实现MyString有成员函数MyString* stringcat(MyString *pString)即为一般的字符串连接,类和它的子类MyNumString(顾名思义，里面只能是数字串),其中它的连接函数要用加法加起来，比如23,和34的话，它们连接起来就是57了，不是2334。请编程并实现它们的多态性.
