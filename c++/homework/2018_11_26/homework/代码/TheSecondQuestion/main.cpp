#include <iostream>
#include "MyClock.h"

using namespace std;

int main()
{
  CMyClock myClock;

  //����ʱ��
  myClock.setTime(12, 0, 0);
  //��ʾʱ��
  myClock.showTime();

  //����get����
  cout << "ʱ:" << myClock.getHour() << endl;
  cout << "��:" << myClock.getMinute() << endl;
  cout << "��:" << myClock.getSecond() << endl;

  getchar();
  return 0;
}