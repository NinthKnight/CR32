#include "MyClock.h"
#include <stdio.h>

/*
  设置时间
*/
void CMyClock::setTime(int nHour, int nMinute, int nSecond)
{
  //设置时间
  this->m_nHour = nHour;
  //设置分
  this->m_nMinute = nMinute;
  //设置秒
  this->m_nSecond = nSecond;
}

/*
  显示时间
*/
void CMyClock::showTime()
{
  //打印时间
  printf("%02d:%02d:%02d\r\n", this->m_nHour, this->m_nMinute, this->m_nSecond);

  return;
}

//获取时
int CMyClock::getHour()
{
  return (this->m_nHour);
}

//获取分
int CMyClock::getMinute()
{
  return (this->m_nMinute);
}

//获取秒
int CMyClock::getSecond()
{
  return (this->m_nSecond);
}