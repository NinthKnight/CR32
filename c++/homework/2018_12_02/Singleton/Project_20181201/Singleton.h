#pragma once
class Singleton
{
public:
  ~Singleton();
  static Singleton* getInstance();

private:
  Singleton();
  static Singleton* instance;

};

