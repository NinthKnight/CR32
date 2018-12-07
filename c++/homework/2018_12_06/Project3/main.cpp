/*举例说明构造函数和析构函数中调用虚函数是否是虚调用，为什么？*/

#include <iostream>
class CClassA
{
public:
    virtual void func()
    {
        std::cout << "CClassA::func" << std::endl;
    }
    CClassA()
    {
        func();//直接调用
    }
    ~CClassA()
    {
        func();
    }
};

int main()
{
    CClassA ca;
    return 0;
}