#include "stdafx.h"
#include "setdisplay.h"


/*********************************
测试函数 & 例子
**********************************/
void TestWindowSizeAndColor()
{
  // 1. 设置控制台标题和窗口大小
  SetWindowSize("控制台颜色测试用例" , // 标题
                30, // 高度 30 行 // 在1920*1080的显示器中最大值为60
                30  // 宽度 30 列 // 1 列 = 1 个汉字 或 2 个英文 
                );

  // 2. 在第一行输出一段带背景的文字
  WriteChar(0 ,  // 第 1 行
            0 ,  // 第 1 列
            "这是一段带背景的文字0123456789ABCDEF" ,
            SetConsoleColor( COLOR_BLACK , // 黑色前景
                             COLOR_WHITE)  // 白色背景
            );


  // 3. 在第三行输出一行淡浅绿色
  char szBuff[ MAXBYTE ] = { 0 };
  // 设置一个内容为60个空格的字符串
  sprintf_s(szBuff , MAXBYTE , "%60c" , ' ');
  WriteChar(2 ,  // 第 3 行
            0 ,  // 第 1 列
            szBuff ,   // 60个空格
            SetConsoleColor( COLOR_BLACK , // 黑色前景
                             COLOR_THIN_LIGHT_GREEN )  // 淡浅绿色
            );
            

  // 4. 在第五行输出一段浅绿色换行文字
  WriteChar(4 ,  // 第 5 行
            0 ,  // 第 1 列
            "这是一段换行的白文字\n0123456789ABCDEF<--这些文字被输出到了第六行，并且支持自动换行，多余的内容会自动到下一行" ,
            COLOR_THIN_GREEN
            );


  // 5. 在屏幕中间打印16种颜色
  // 主要方法通过给空格设置背景色
  for(int i = 0; i < 0x04; ++i)
  {
    for(int j = 0; j < 0x04; ++j)
    {
      WriteChar(i + 12 , // 从第13行开始
                j + 12 , // 从第13列开始
                "  " , // 两个空格
                SetConsoleColor( COLOR_BLACK , // 黑色前景 
                                 (WORD)(i * 4 + j) )    // 背景色
                );
    }
  }


  // 6. 在倒数第三行输出一段带背景的符号
  WriteChar(27 ,  // 第 28 行
            0 ,   // 第 1 列
            "符号：§№☆★○●◎◇◆□■△▲※→←↑↓〓＃＠＆＼＾＿￣  " ,
            SetConsoleColor( COLOR_THIN_BLUE ,   // 浅蓝前景
                             COLOR_LIGHT_WHITE)  // 亮白色背景
            );


  // 7. 在最后一行输出一行亮白色
  WriteChar(29 ,  // 第 30 行
            0 ,  // 第 1 列
            szBuff,
            SetConsoleColor( COLOR_BLACK , // 黑色前景
                             COLOR_LIGHT_WHITE )  // 亮白色背景
            );


  // 8. 问题展现
  // 在最后多出的一行输出内容
  WriteChar(30 ,  // 第 31 行
            0 ,   // 第 1 列
            "无法避免的Bug描述:设置30行,但这是第31行,再多加个空格来试试 " ,
            SetConsoleColor( COLOR_THIN_BLUE ,   // 浅蓝前景
                             COLOR_LIGHT_WHITE)  // 亮白色背景
            );
}


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
*************************************/
void WriteChar(int nHigh , int nWide , char* pszChar , WORD wArr)
{
	CONSOLE_CURSOR_INFO cii;
	cii.dwSize = 1;
	cii.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE) , &cii);
	COORD loc;
	loc.X = nWide * (WIDTH_UNIT);
	loc.Y = nHigh;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , wArr);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE) , loc);
	printf(pszChar);
}


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
BOOL SetWindowSize(char *pszWindowTitle , int nHight, int nWide)
{
	// Title
  nWide *= (WIDTH_UNIT);
  // nHight -= 1;
  nWide -= 1;
	SetConsoleTitleA(pszWindowTitle);
	HANDLE hStdin , hStdOut;
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	// get max console window size
	COORD pos = GetLargestConsoleWindowSize(hStdOut);
	COORD BufferSize = { pos.X , pos.Y };
	// set console buffer size
	if(!SetConsoleScreenBufferSize(hStdOut , BufferSize)){
		// set console buffer size FALSE
		printf("buffer err(%d,%d)%d\n" , BufferSize.X , BufferSize.Y , GetLastError());
		return FALSE;
	}
	SMALL_RECT srctWindow = { 0 , 0 , nWide , nHight };
	if(!SetConsoleWindowInfo(hStdOut , TRUE , &srctWindow)){
		// set console window size FALSE
		printf("size err %d\n" , GetLastError());
		return FALSE;
	}
	COORD Buffer = { nWide + 1 , nHight + 1 };
	// set console buffer size
	if(!SetConsoleScreenBufferSize(hStdOut , Buffer)){
		// set console buffer size FALSE
		printf("buffer err(%d, %d)%d\n" , BufferSize.X , BufferSize.Y , GetLastError());
		return FALSE;
	}
	return TRUE;
}
