#include <iostream>
/*
5.创建一个有很多数据成员的类，这些成员分布在public
,private和protected所指定的区域中。增加一个成员函数showMap()
,该成员函数打印出这些数据成员的名字和它们的地址。如果有可能，
在多个编译器、操作系统中编译运行这个程序，看目标代码中布局
是否一样。
*/

class classA
{
private:
  int priA;
  int priB;
protected:
  int proA;
  int proB;
public:
  int pubA;
  int pubB;

  void showMap()
  {
    printf("private:\r\n");
    printf("\tpriA\t0x%p\r\n", &this->priA);
    printf("\tpriB\t0x%p\r\n", &this->priB);

    printf("\r\nprotected:\r\n");
    printf("\tproA\t0x%p\r\n", &this->proA);
    printf("\tproB\t0x%p\r\n", &this->proB);

    printf("\r\npublic:\r\n");
    printf("\tpubA\t0x%p\r\n", &this->pubA);
    printf("\tpubA\t0x%p\r\n", &this->pubB);
  }
};

int main()
{
  classA ca;
  ca.showMap();

  getchar();
  return 0;
}