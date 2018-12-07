#include <iostream>

class IPerson 
{
public:
    virtual void Speak() = 0;
    virtual void Eat() = 0;
};

class CChinese : public IPerson
{
public:
    virtual void Speak() 
    {
        std::cout << "CChinese::Speak(ººÓï)" << std::endl;
    }
};

int main()
{
    CChinese chs;
    return 0;
}

