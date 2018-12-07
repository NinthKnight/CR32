/*在昨天的题目1中，使得draw()是纯虚函数。尝试创建一个类型为Shape的对象。
并试着在构造函数内调用这个纯虚函数，看看结果如何。保留它的纯虚性，对draw()进行定义。*/

#include <iostream>

//class CShape
//{
//public:
//    virtual void draw() = 0;
//    CShape()
//    {
//        draw();
//    }
//};

class IShape
{
public:
    virtual void draw() = 0;
};
class CCircle : public IShape
{
public:
    void draw()
    {
        std::cout << "draw CCircle" << std::endl;
    }
};
class CSquare : public IShape
{
public:
    void draw()
    {
        std::cout << "draw CSquare" << std::endl;
    }
};
class CTriangle : public IShape
{
public:
    void draw()
    {
        std::cout << "draw CTriangle" << std::endl;
    }
};

int main()
{
    //CShape shape;//不允许实例化

}