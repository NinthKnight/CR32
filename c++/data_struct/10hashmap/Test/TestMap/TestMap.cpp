// TestMap.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <map>

void foo_map() {

    std::map<int, int> mp;

    mp.insert(std::pair<int, int>(3, 30));
    mp.insert(std::pair<int, int>(1, 10));
    mp.insert(std::pair<int, int>(2, 20));
    mp.insert(std::pair<int, int>(5, 50));

    int n = mp[1];
  
    for (auto it = mp.begin(); it != mp.end(); it++){
        
        printf("%d:%d ", it->first, it->second);

    }

    //�����˼·

    //aaacccccccccccccccccccccccccccccccccccddddeffffffgffffhhhhhhh





    /*
        a 000  010   3��
        b 001        0��
        c 010  01    35��
        d 011        4��
        e 100        1��
        f 101        10��
        g 110        1��
        h 111        7��

      ����ʹ�õĴ�������
        c     10��
        f     6��
        h     5��
        d     4��
        a     3��
          
                   28
                18     c
             12     f
          7     h
        a   d

        c: 1      10   =  10
        f: 01      6   =  12
        h: 001     5   =  15
        a: 0000    3   =  12
        d: 0001    4   =  16
        --------------------------
                          65

  
          11
        f   h
                28
            17      11
          7    c  f   h 
        a   d  


        c 01   10  = 20
        f 10   6   = 12
        h 11   5   = 10
        a 000  3   = 9
        d 001  4   = 12
    -------------------------
                     63



        g   b
        

    
    */



    return;
}


int main()
{
    foo_map();

    return 0;
}

