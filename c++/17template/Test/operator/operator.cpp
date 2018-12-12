// operator.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

//匿名类
//class {
//
//
//} obj;


//转换运算符

//class CInt {
//public:
//    CInt() {
//        m_nInt = 0;
//    }
//
//    //转换运算符
//    operator int() {
//        return m_nInt;
//    }
//
//private:
//    int m_nInt;
//};

template<typename T>
class CInt {
public:
    CInt() {
        m_nInt = 0;
    }

    //转换运算符
    operator T() {
        return m_nInt;
    }

private:
    T m_nInt;
};

//变体
class CVarient {
public:

    enum VT_TYPE{
        VT_INT,
        VT_FLOAT
    };

    int operator=(int n) {
        m_Type = VT_INT;
        m_data.m_nInt = n;
        return n;
    }

    float operator=(float f) {
        m_Type = VT_FLOAT;
        m_data.m_float = f;

        return f;
    }

    friend ostream& operator<<(ostream& cout, CVarient& obj);

private:
    
    union unVar{
        int m_nInt;
        float m_float;
    };

    VT_TYPE m_Type;
    unVar m_data;
};


ostream& operator<<(ostream& cout, CVarient& obj)
{
    if (obj.m_Type == CVarient::VT_INT) {
        cout << obj.m_data.m_nInt;
    }
    else  if (obj.m_Type == CVarient::VT_FLOAT) {
        cout << obj.m_data.m_float;
    }

    return cout;
}


int main()
{
    //var;
    CVarient var;
    
    var = 123;
    cout << var << endl;

    var = 1.2f;
    cout << var << endl;



    //CInt<double> n;
    //double k = n + 3.0;
 
    return 0;
}

