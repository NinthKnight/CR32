/*
  时钟类
*/
class CMyClock
{
private: //属性封装
  //时
  int m_nHour;
  //分
  int m_nMinute;
  //秒
  int m_nSecond;

public: //行为封装
  //设置时间
  void setTime(int nHour, int nMinute, int nSecond);
  //显示时间
  void showTime();

  //获取时间
  int getHour();
  //获取分钟
  int getMinute();
  //获取秒
  int getSecond();
};