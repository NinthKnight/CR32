#include <iostream>

class classA
{
public:
  int pubA;
private:
  int priA;
protected:
  int proA;
};

int main()
{
  classA c;
  c.pubA = 0;

  c.priA = 0;
  c.proA = 0;

  getchar();
  return 0;
}