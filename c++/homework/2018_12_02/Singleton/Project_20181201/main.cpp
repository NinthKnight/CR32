#include <iostream>
#include "Singleton.h"

int main()
{
  //Singleton obj = Singleton();//����ʵ��������
  //Singleton obj;//����ʵ��������
  Singleton *obj = Singleton::getInstance(); //ֻ���ڵ���
  Singleton *obj2 = Singleton::getInstance(); //ֻ���ڵ���
  
  std::cout << obj << "," << obj2 << std::endl;

  getchar();
  return 0;
}