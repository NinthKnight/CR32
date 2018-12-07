/*举例说明为什么析构函数通常都是虚函数？*/
#include <iostream>

class Base
{
public:
    virtual void func1()
    {
        std::cout << "Base::func1()" << std::endl;
    }
    virtual void func2()
    {
        std::cout << "Base::func2()" << std::endl;
    }
    Base()
    {
        std::cout << "Base::Base()" << std::endl;
    }
    virtual ~Base()
    {
        std::cout << "Base::~Base()" << std::endl;
    }
};

class Derived : public Base
{
public:
    void func1()
    {
        std::cout << "Derived::func1()" << std::endl;
    }
    void func2()
    {
        std::cout << "Derived::func2()" << std::endl;
    }

    void func3()
    {
        Derived::func1();
        this->func1();
        std::cout << "Derived::func3()" << std::endl;
    }

    Derived()
    {
        std::cout << "Derived::Derived()" << std::endl;
    }
    ~Derived()
    {
        std::cout << "Derived::~Derived()" << std::endl;
    }
};

int main()
{
    //如果不用虚析构，delete调用的是父类的析构函数。
    Derived* pDer = new Derived;
    Base* pBase = pDer;
    delete pBase;
    return 0;
}