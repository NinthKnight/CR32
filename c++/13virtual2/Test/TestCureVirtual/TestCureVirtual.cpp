// TestCureVirtual.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


//抽象类提供接口，本质：决定虚表对应函数的位置
//抽象类通常不写数据成员，只提供接口。

//纯虚函数不用写实现
//一个类如果有纯虚函数，则是抽象类，不能实例化。
//子类继承父类的纯虚函数，只要有一个纯虚函数不实现，则仍然是抽象类，不能实例化。

//interface
class IPerson {
public:
    virtual void Speak() = NULL; //纯虚函数

    //int m_n;
};

//void CPerson::Speak() {
//    printf("CPerson::Speak(人话)\r\n");
//}

class CChinese : public IPerson {
public:
    virtual void Speak() {
        printf("CChinese::Speak(汉语)\r\n");
    }

};

int main()
{
    CChinese chs;
    chs.Speak();

    //CPerson per;
    //per.Speak();


    return 0;
}

