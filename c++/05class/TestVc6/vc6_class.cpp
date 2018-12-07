
#include <stdio.h>

class tagClock {

private:
    //����
    int nHour;
    int nMinute;
    int nSecond;

public:
    //��Ϊ,��������,����
    int SetTime(int nH, int nM, int nS){
      
      nHour = nH;
      nMinute = nM;
      nSecond = nS;
      
      return 0;
    }
};

//���еĺ���ָ��
typedef int(tagClock::*PFN_SetTimeClass)(int nH, int nM, int nS);



int main(int argc, char* argv[]){
  
  tagClock cl1;
  tagClock cl2;
  
  PFN_SetTimeClass pfn1 = cl1.SetTime;
  PFN_SetTimeClass pfn2 = cl2.SetTime;
  
  //��ַ��һ���ģ���ʾͬһ����Ķ���ĳ�Ա�����ǹ��õ�
  //��1�������Ƕ����ġ�
  //��2����Ա�����ǹ��õ�
  
  cl1.SetTime(1, 2 ,3);
  cl2.SetTime(4, 5, 6);
  
  printf("pfn1 = %p\r\n", pfn1);
  printf("pfn2 = %p\r\n", pfn2);
  
  
  return 0;
}