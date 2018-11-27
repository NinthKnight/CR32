#pragma once
#include <windows.h>
#include <stdio.h>

/********控制台输出控制彩色内容*********/

/*************************************
这个彩色控制台的一个小问题：
    会比设置的高度多一行（最后一行），
    这一行可以输出内容，
    但不要输出内容到最后一列，
    否则界面会被挤下来一行，第一行会消失，
    意味着在设置满屏背景的情况下，
    要不最后一行全黑，
    要不右下角留一个窄黑块，
    测试&例子代码中第8个测试可以展示问题
**************************************/


/*********** 宽度的基本单位（整数） ***********/
// 设置为2意味着1列为2个英文宽度或1个汉字宽度      
#define WIDTH_UNIT 2  // 可根据需求修改



/*************************************
颜色属性
**************************************/
#define COLOR_BLACK             0x00    // 黑色
#define COLOR_BLUE              0x01    // 蓝色
#define COLOR_GREEN             0x02    // 绿色
#define COLOR_LIGHTBLUE         0x03    // 湖蓝色
#define COLOR_RED               0x04    // 红色
#define COLOR_PURPLE            0x05    // 紫色
#define COLOR_YELLOW            0x06    // 黄色
#define COLOR_WHITE             0x07    // 白色
#define COLOR_GRAY              0x08    // 灰色
#define COLOR_THIN_BLUE         0x09    // 淡蓝色
#define COLOR_THIN_GREEN        0x0A    // 淡绿色
#define COLOR_THIN_LIGHT_GREEN  0x0B    // 淡浅绿色
#define COLOR_THIN_RED          0x0C    // 淡红色
#define COLOR_THIN_PURPLE       0x0D    // 淡紫色
#define COLOR_THIN_YELLOW       0x0E    // 淡黄色
#define COLOR_LIGHT_WHITE       0x0F    // 亮白色


/*******************************
功能：设置前背景色

f 前景色
b 背景色

原理：
  1字节数据
  低4字节为前景，高4字节为背景
********************************/
#define SetConsoleColor( f , b ) ( ( f ) + ( ( b ) << 0x04 ) )


/***********************************
测试函数 & 例子
************************************/
void TestWindowSizeAndColor();


/*************************************
函数功能：打印字符到控制台制定位置
nHigh: 高度X行，行数
nWide: 宽度Y列，列数
pszChar: 打印的字符串（一个字符也要用字符串的形式）
wArr: 打印字符的属性：颜色
      可通过SetConsoleColor宏设置背景色

注意: 数据显示到界面上后会一直存在
      宽度 1 列为 1 个汉字 或 两个英文，
      可通过 宽度宏 WIDTH_UNIT 来控制
**************************************/
void WriteChar(int nHigh , int nWide , char* pszChar , WORD wArr);


/*************************************
函数功能: 设置窗口信息
*pszWindewTitle: 窗口名称
nHigh: 高度X行，行数
nWide: 宽度Y列，列数
成功返回值: TRUE

注意：数值设置太大会出错，尤其是高度
      宽度 1 列为 1 个汉字 或 两个英文，
      可通过 宽度宏 WIDTH_UNIT 来控制
*************************************/
BOOL SetWindowSize(char *pszWindowTitle , int nHigth, int nWide);

