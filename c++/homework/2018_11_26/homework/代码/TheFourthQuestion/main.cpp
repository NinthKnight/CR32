#include <iostream>

using namespace std;

class classA
{
public:
  void fooA()
  {
    cout << "classA::fooA" << endl;
  }
};

class classB
{
public:
  void fooA(classA *p)
  {
    p->fooA();
  }
};

/*
  ����������
*/
int main()
{
  classA ca;
  classB cb;

  ca.fooA();
  cb.fooA(&ca);

  getchar();
  return 0;
}