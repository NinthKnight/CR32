#include <stdio.h>

//函数指针定义
typedef void(__cdecl *FPN_SetTime)(struct tagClock *pClock, int nH, int nM, int nS);
typedef void(__cdecl *FPN_ShowTime)(struct tagClock *pClock);

struct tagClock
{
  //时
  int nHour;
  //分
  int nMinute;
  //秒
  int nSecond;

  //设置时间
  FPN_SetTime setTime;
  //显示时间
  FPN_ShowTime showTime;
};

void setTime(struct tagClock *pClock, int nH, int nM, int nS)
{
  //设置时
  pClock->nHour = nH;
  //设置分
  pClock->nMinute = nM;
  //设置秒
  pClock->nSecond = nS;
}

void showTime(struct tagClock *pClock)
{
  printf("%02d:%02d:%02d\r\n", pClock->nHour, pClock->nMinute, pClock->nSecond);
}


int main()
{
  //初始化
  struct tagClock cl;
  cl.setTime = setTime;
  cl.showTime = showTime;

  //调用接口
  cl.setTime(&cl, 21, 12, 33);
  cl.showTime(&cl);

  getchar();
  return 0;
}