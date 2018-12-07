#include "MyClock.h"
#include <stdio.h>

/*
  ����ʱ��
*/
void CMyClock::setTime(int nHour, int nMinute, int nSecond)
{
  //����ʱ��
  this->m_nHour = nHour;
  //���÷�
  this->m_nMinute = nMinute;
  //������
  this->m_nSecond = nSecond;
}

/*
  ��ʾʱ��
*/
void CMyClock::showTime()
{
  //��ӡʱ��
  printf("%02d:%02d:%02d\r\n", this->m_nHour, this->m_nMinute, this->m_nSecond);

  return;
}

//��ȡʱ
int CMyClock::getHour()
{
  return (this->m_nHour);
}

//��ȡ��
int CMyClock::getMinute()
{
  return (this->m_nMinute);
}

//��ȡ��
int CMyClock::getSecond()
{
  return (this->m_nSecond);
}