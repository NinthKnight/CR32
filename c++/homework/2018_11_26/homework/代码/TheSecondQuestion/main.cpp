#include <iostream>
#include "MyClock.h"

using namespace std;

int main()
{
  CMyClock myClock;

  //设置时间
  myClock.setTime(12, 0, 0);
  //显示时间
  myClock.showTime();

  //调用get方法
  cout << "时:" << myClock.getHour() << endl;
  cout << "分:" << myClock.getMinute() << endl;
  cout << "秒:" << myClock.getSecond() << endl;

  getchar();
  return 0;
}