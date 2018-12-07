/*将学员录入程序中的学生和老师加入多态性，
以适应不同的学生(学生都有说话成员函数可能有的学生是聋哑生，他们的说话方法即为手语)
和老师的多态性(老师分为老教师和新教师，老教师都用正常教学，新教师喜欢用多媒体教学，老师有教学这个成员方法)*/

#include <iostream>
class CStudent
{
public:
    virtual void Express() = 0; //表达
};
class CTeacher
{
public:
    virtual void Teach() = 0; 
};

class CNormalStu : public CStudent
{
public:
    void Express()
    {
        std::cout << "普通学生说话" << std::endl;
    }
};
class CDisabledStu : public CStudent
{
public:
    void Express()
    {
        std::cout << "聋哑生:手语" << std::endl;
    }
};

class COldTea : public CTeacher
{
public:
    void Teach()
    {
        std::cout << "正常教学" << std::endl;
    }
};
class CNewTea : public CTeacher
{
public:
    void Teach()
    {
        std::cout << "多媒体教学" << std::endl;
    }
};

int main()
{
    CNormalStu normalStu;
    CDisabledStu disabledStu;
    COldTea oldTea;
    CNewTea newTea;
    ((CStudent*)(&normalStu))->Express();
    ((CStudent*)(&disabledStu))->Express();
    ((CTeacher*)(&oldTea))->Teach();
    ((CTeacher*)(&newTea))->Teach();


    return 0;
}