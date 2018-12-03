#include <iostream>
#include "CMystring.h"
using namespace std;
//µÚ¶şÌâ
int main()
{
  CMystring str = "helloworld";

  CMystring str2;

  str2 = "what this help";

  str2.Cat(str);

  cout << str.GetStr() << endl;

  cout << str2.GetStr() << endl;

  str.Format("%s:%d", "127.0.0.1", 8080);

  cout << str.GetStr() << endl;

  CMystring str3 = str2;
  str2.ReleaseSelf();

  cout << str3.GetStr() << endl;

  getchar();
  return 0;
}
