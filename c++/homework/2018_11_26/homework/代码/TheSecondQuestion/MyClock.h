/*
  ʱ����
*/
class CMyClock
{
private: //���Է�װ
  //ʱ
  int m_nHour;
  //��
  int m_nMinute;
  //��
  int m_nSecond;

public: //��Ϊ��װ
  //����ʱ��
  void setTime(int nHour, int nMinute, int nSecond);
  //��ʾʱ��
  void showTime();

  //��ȡʱ��
  int getHour();
  //��ȡ����
  int getMinute();
  //��ȡ��
  int getSecond();
};