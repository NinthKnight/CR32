/*写一个员工类,其中有发薪水的方法。
写一个项目经理类，他继承自员工类。写一个程序员类，也继承自员工类。
请实现并表现出他们发薪水的多态性*/
#include <iostream>

class CEmployee
{
public:
    virtual void Payoff() = 0;
};

class CManager : public CEmployee
{
public:
    void Payoff()
    {
        std::cout << "给经理发钱" << std::endl;
    }
};

class CProgrammer : public CEmployee
{
public:
    void Payoff()
    {
        std::cout << "给程序员发钱" << std::endl;
    }
};

int main()
{
    CManager mam;
    CProgrammer prg;
    ((CEmployee*)&mam)->Payoff();
    ((CEmployee*)&prg)->Payoff();
    return 0;
}