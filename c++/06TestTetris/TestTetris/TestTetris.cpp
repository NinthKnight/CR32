// TestTetris.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "setdisplay.h"
#include "Sense.h"

int main()
{
    srand(time(NULL));
    // 1. 设置控制台标题和窗口大小
    SetWindowSize("控制台颜色测试用例", // 标题
        30, // 高度 30 行 // 在1920*1080的显示器中最大值为60
        30  // 宽度 30 列 // 1 列 = 1 个汉字 或 2 个英文 
        );
    
   
    CSense sense;
    sense.Init();

    while (true) {

        int nOffset = 10;
        //清空颜色
        for (int i = 0; i < 4; i++)
        {
            //分别打印出四个坐标点
           /* ShowBlock(block.X(i) + 10,
                      block.Y(i) + 10);*/
        }

        
        if (_kbhit()) {
            char ch;
            ch = _getch();


          /*  clearBg();
            if (ch == 'a') {
                block.LeftRotate();

            }
            else if (ch == 'd') {
                block.RightRotate();
            }*/
        }   
        

       
    }
    
    

    return 0;
}

