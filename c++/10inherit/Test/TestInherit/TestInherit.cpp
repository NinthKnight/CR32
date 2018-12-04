// TestInherit.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <iostream>

//面向对象：继承
//

//学生 教师 职工
//冗余：增加，修改，删除麻烦

class CPerson {
public:
    CPerson(int nGender){
        m_nGender = nGender;
        m_nPublic =   0xAAAAAAAA;
        m_protected = 0xBBBBBBBB;
        m_private =   0xDDDDDDDD;
    }

    int Gender() {
        return m_nGender;
    }

    void SetGender(int nGender) {
        m_nGender = nGender;
        //this->m_nTeaId = 2;
    }

public:
    //std::string m_strName; //姓名
    int m_nGender; //性别
    int m_nPublic;
    int n;

protected:
    int m_protected;

private:
    int m_private;
};

//类与类的关系:
//组合关系：学生有人的属性   (has-a) 
class CStudent {
public:
    CStudent(int StuId, int nGender) 
        :m_nStuId(StuId), m_per(nGender)
    {
    
    }

    void SetGender(int nGender) {
        m_per.SetGender(nGender);
    }



private:
    CPerson m_per;
    int m_nStuId;  //学号
};

//继承关系：老师是一个人    （is-a）
//从人类中继承：
//  1.成员数据（性别）
//  2.成员函数（get ,set）
//称呼：
// CPerson ---> 基类    /   父类
// CTeacher ---> 派生类 /   子类


// 动物--人、黑猩猩 、鸟
// 交通工具--飞机，车，船
// 车--汽车，火车，摩托车，自行车
// 汽车--比亚迪，雪佛兰，奥迪
// 奥迪--A4,A8,A9
// Object  对象
// MFC --> CObject
// Qt  --> QObject

class CTeacher: public CPerson {
public:
    CTeacher(int TeaId, int nGender)
        :m_nTeaId(TeaId), CPerson(nGender)
    {
        m_nGender = 3;

        //m_nPublic = 1;
        //m_protected = 2;
        //m_private = 3;
    }

    void teach() {
        std::cout << "teach" << m_nTeaId << std::endl;
        CPerson::n = 3;
    }

private:
    int n;
    int m_nTeaId;  //工号
};

//访问权限
/*
保护成员（protected）：保护成员除了自身或者派生类以外，不能在其他类外使用。
这个访问权限是在编译时期做的检查，实际子类的对象的内存中包含父类所有成员。
        父类（CPerson）   <--   公有继承public     --     子类(CTeacher)                        
公有成员（public）                                      公有成员（public）
保护成员（protected）                                   保护成员（protected）
私有成员（private）                                     不可见

                     父类   <--   保护继承protected   --    子类                         
公有成员（public）                                       保护成员（protected）
保护成员（protected）                                    保护成员（protected）
私有成员（private）                                      不可见

                     父类   <--   私有继承private     --    子类                         
公有成员（public）                                       不可见
保护成员（protected）                                    不可见
私有成员（private）                                      不可见

*/

/*
    构造，析构顺序：
    构造：先父类，再子类
    析构：先子类，再父类

    父类，子类，朋友类

*/

/*
    数据隐藏：
         

*/

int n = 1;
int main()
{
    int n = 2;
    //CStudent stu(1, 2);

    //stu.SetGender(1);
    //int nSize = sizeof(stu);

    CPerson* aryObj[2];

    CPerson per(1);
    //per.m_protected = 2;

    CTeacher tea(1, 2);
    //tea.m_nPublic = 1;
    //tea.m_protected = 2;

    aryObj[0] = &per;
    aryObj[1] = &tea;

    CTeacher* pTea = &tea;
    
    //类型转换：向上转换，子类指针（引用）转换为父类指针（引用）， 安全的
    CPerson* pPer = pTea;
    pPer->SetGender(1);

    //类型转换：向下转换，父类指针（引用）转换为子类指针（引用）， 不安全的,导致访问越界
    CTeacher* pTea2 = (CTeacher*)&per;

    pTea2->teach();

    //唯一的安全的情况：
    CTeacher* pTea3 = (CTeacher*)pPer;
    pTea3->teach();


    tea.SetGender(1);
    int nSize = sizeof(tea);

    return 0;
}

