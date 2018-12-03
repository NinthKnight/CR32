#include "CTetrisUI.h"
#include <Windows.h>
#include <iostream>

/*
获取控制台尺寸
*/
SMALL_RECT CTetrisUI::SizeOfConsole(HANDLE handle) {
  CONSOLE_SCREEN_BUFFER_INFO info;
  GetConsoleScreenBufferInfo(handle, &info);
  return info.srWindow;
}

CTetrisUI::CTetrisUI()
{
  stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);

  //隐藏光标
  CONSOLE_CURSOR_INFO cci = { 1, 0 };
  SetConsoleCursorInfo(stdHandle, &cci);

  //去除滚动条
  SMALL_RECT rect = SizeOfConsole(stdHandle);
  COORD size = { rect.Right + 1,rect.Bottom + 1 };
  SetConsoleScreenBufferSize(stdHandle, size);

  //设置标题
  SetConsoleTitleA("Tetris v1.0");

}

CTetrisUI::~CTetrisUI()
{
}

void CTetrisUI::DrawString(int x, int y, const char * str, CTetrisUI::emColor color)
{
  //移动光标
  MovePostion(x, y);

  //写入字符
  SetConsoleTextAttribute(stdHandle, Colors[color]);
  printf(str);
  SetConsoleTextAttribute(stdHandle, FOREGROUND_INTENSITY);
}

/*
  指定位置填空
*/
void CTetrisUI::ClearSpace(int x, int y, int nSize)
{
  //构造空字串
  char *buf = new char[nSize + 1] { 0 };

  ::memset(buf, ' ', nSize);
  
  DrawString(x, y, buf, GRAY);
  delete buf;
}

/*
  拷贝屏幕一行
*/
void CTetrisUI::CopyLine(int nLine, int nCopyLine, int nSize)
{
  SMALL_RECT srctReadRect;
  srctReadRect.Top = nCopyLine;    
  srctReadRect.Left = 0;
  srctReadRect.Bottom = nCopyLine;
  srctReadRect.Right = nSize;

  COORD coordBufSize;
  COORD coordBufCoord;
  coordBufSize.Y = nCopyLine;
  coordBufSize.X = nSize;

  coordBufCoord.X = 0;
  coordBufCoord.Y = 0;

  CHAR_INFO chiBuffer[1 * 80]; 
  BOOL fSuccess;
  fSuccess = ReadConsoleOutput(stdHandle, chiBuffer, coordBufSize, coordBufCoord, &srctReadRect);

  SMALL_RECT srctWriteRect;
  
  srctWriteRect.Top = nLine;
  srctWriteRect.Left = 0;
  srctWriteRect.Bottom = nLine; 
  srctWriteRect.Right = nSize;

  fSuccess = WriteConsoleOutput(stdHandle, chiBuffer, coordBufSize, coordBufCoord, &srctWriteRect);

}

void CTetrisUI::MovePostion(int x, int y)
{
  COORD pos = { 0 };
  pos.X = (short)x * 2;
  pos.Y = (short)y;
  SetConsoleCursorPosition(stdHandle, pos);
}

void CTetrisUI::SetGroundColor(emColor color)
{
  SetConsoleTextAttribute(stdHandle, Colors[color]);
}

void CTetrisUI::GameOver()
{
  DWORD numSize = 0;

  //填充背景
  for (short i = 0; i < 4; i++) {
    FillConsoleOutputCharacterA(stdHandle, ' ', 22, { (short)30, (short)9 + i }, &numSize);
    FillConsoleOutputAttribute(stdHandle, BACKGROUND_GREEN | BACKGROUND_INTENSITY, 22, { (short)30, (short)9 + i }, &numSize);
  }

  //GameOver
  SetConsoleCursorPosition(stdHandle, { (short)36, (short)10 });
  SetConsoleTextAttribute(stdHandle, FOREGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
  WriteConsoleA(stdHandle, "GameOver!\n", 10, NULL, NULL);
  //
  SetConsoleCursorPosition(stdHandle, { (short)32, (short)11 });
  WriteConsoleA(stdHandle, "按回车键退出游戏...", 19, NULL, NULL);

  SetConsoleTextAttribute(stdHandle, 0);
  MovePostion(28, 1);
}

const unsigned short Colors[CTetrisUI::COLORCOUNT] =
{
  FOREGROUND_INTENSITY,//墙壁的颜色
  FOREGROUND_RED | FOREGROUND_INTENSITY,
  FOREGROUND_GREEN | FOREGROUND_INTENSITY,
  FOREGROUND_BLUE | FOREGROUND_INTENSITY,
  FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
  FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
  FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
  FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
};