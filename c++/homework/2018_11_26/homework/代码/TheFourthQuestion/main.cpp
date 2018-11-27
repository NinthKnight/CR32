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
  看不懂题意
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