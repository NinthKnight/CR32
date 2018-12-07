#include <iostream>
#include "Singleton.h"

int main()
{
  //Singleton obj = Singleton();//不能实例化对象
  //Singleton obj;//不能实例化对象
  Singleton *obj = Singleton::getInstance(); //只存在单例
  Singleton *obj2 = Singleton::getInstance(); //只存在单例
  
  std::cout << obj << "," << obj2 << std::endl;

  getchar();
  return 0;
}