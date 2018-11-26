
#include <stdio.h>

class tagClock {

private:
    //数据
    int nHour;
    int nMinute;
    int nSecond;

public:
    //行为,函数声明,内联
    int SetTime(int nH, int nM, int nS){
      
      nHour = nH;
      nMinute = nM;
      nSecond = nS;
      
      return 0;
    }
};

//类中的函数指针
typedef int(tagClock::*PFN_SetTimeClass)(int nH, int nM, int nS);



int main(int argc, char* argv[]){
  
  tagClock cl1;
  tagClock cl2;
  
  PFN_SetTimeClass pfn1 = cl1.SetTime;
  PFN_SetTimeClass pfn2 = cl2.SetTime;
  
  //地址是一样的，表示同一个类的对象的成员函数是共用的
  //（1）数据是独立的。
  //（2）成员函数是共用的
  
  cl1.SetTime(1, 2 ,3);
  cl2.SetTime(4, 5, 6);
  
  printf("pfn1 = %p\r\n", pfn1);
  printf("pfn2 = %p\r\n", pfn2);
  
  
  return 0;
}