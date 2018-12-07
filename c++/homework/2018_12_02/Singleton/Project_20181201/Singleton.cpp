#include "Singleton.h"
#include <iostream>

Singleton::Singleton()
{
  std::cout << "Singleton::Singleton()" << std::endl;
}

Singleton::~Singleton()
{
}

Singleton *Singleton::instance = new Singleton();

Singleton * Singleton::getInstance()
{
  if (instance != nullptr)
  {
    return instance;
  }
}
