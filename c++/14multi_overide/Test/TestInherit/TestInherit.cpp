// TestInherit.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <ctime>

/*
    单重继承
    class CChinese : public CPerson

    多重继承
    class A : public B, public C

    //沙发床

*/

//菱形继承 
//家具类
class CFurniture {
public:
    CFurniture() {
        printf("CFurniture::CFurniture()\r\n");
        m_nFurniture = 0;
    }

    void use() {};

    int m_nFurniture;

};

//虚继承
class CSofa : virtual public CFurniture{
public:
    CSofa() {
        printf("CSofa::CSofa()\r\n");
        m_nSofa = 1;
    }
    
    virtual void sit() {
        printf("CSofa::sit()\r\n");
    }

private:
    int m_nSofa;
};

class CBed : virtual public CFurniture {
public:
    CBed() {
        printf("CBed::CBed()\r\n");
        m_nBed = 2;
    }

    void sleep() {
        printf("CBed::sleep()\r\n");
    }

private:
    int m_nBed;
};

//沙发床多重继承 ，既继承了沙发的特点，又继承了床的特点
class CSofaBed : public CSofa, public CBed {
public:
    CSofaBed() {
        printf("CSofaBed::CSofaBed()\r\n");
        m_nSofaBed = 3;
    }

private:
    int m_nSofaBed;
};


/*
    1. 单重继承无虚函数
    2. 单重虚继承无虚函数
    3. 单重继承有虚函数
    4. 单重虚继承有虚函数

    1. 多重继承无虚函数
    2. 多重虚继承无虚函数
    3. 多重继承有虚函数
    4. 多重虚继承有虚函数

    菱形继承
*/


int main()
{
    CSofa sofa;
    int sofaSize = sizeof(CSofa);

    CSofaBed sofaBed;
    
    ////切片
    CSofa* pSofa = &sofaBed;
    CBed* pBed = &sofaBed;


    CFurniture* pFur = &sofaBed;
    //CFurniture* pFur2 = &sofaBed;
    sofaBed.m_nFurniture = 1;

    int nSize = sizeof(CSofaBed);

    //sofaBed.CSofa::m_nFurniture = 1;
    //sofaBed.CBed::m_nFurniture = 1;
    //sofaBed.sit();

    //sofaBed.sleep();

    ////切片
    //CSofa* pSofa = &sofaBed;
    //CBed* pBed = &sofaBed;

    return 0;
}

