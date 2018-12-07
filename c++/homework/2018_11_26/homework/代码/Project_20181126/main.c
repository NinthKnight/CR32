#include <stdio.h>

//����ָ�붨��
typedef void(__cdecl *FPN_SetTime)(struct tagClock *pClock, int nH, int nM, int nS);
typedef void(__cdecl *FPN_ShowTime)(struct tagClock *pClock);

struct tagClock
{
  //ʱ
  int nHour;
  //��
  int nMinute;
  //��
  int nSecond;

  //����ʱ��
  FPN_SetTime setTime;
  //��ʾʱ��
  FPN_ShowTime showTime;
};

void setTime(struct tagClock *pClock, int nH, int nM, int nS)
{
  //����ʱ
  pClock->nHour = nH;
  //���÷�
  pClock->nMinute = nM;
  //������
  pClock->nSecond = nS;
}

void showTime(struct tagClock *pClock)
{
  printf("%02d:%02d:%02d\r\n", pClock->nHour, pClock->nMinute, pClock->nSecond);
}


int main()
{
  //��ʼ��
  struct tagClock cl;
  cl.setTime = setTime;
  cl.showTime = showTime;

  //���ýӿ�
  cl.setTime(&cl, 21, 12, 33);
  cl.showTime(&cl);

  getchar();
  return 0;
}