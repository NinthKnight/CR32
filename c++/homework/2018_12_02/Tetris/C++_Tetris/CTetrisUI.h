#pragma once
#include <Windows.h>

class CTetrisUI
{
public:
  //颜色列表
  enum emColor
  {
    GRAY,
    RED,
    GREEN,
    BLUE,
    YELLOW,
    WHITE,
    PINK,
    UNKNOW,
    COLORCOUNT = 8
  };

public:
  CTetrisUI();
  ~CTetrisUI();
  void DrawString(int x, int y, const char * str, emColor color);

  void ClearSpace(int x, int y, int nSize);

  void CopyLine(int nLine, int nCopyLine, int nSize);

  void MovePostion(int x, int y);

  void SetGroundColor(emColor color);
  
  void GameOver();

private:
  SMALL_RECT SizeOfConsole(HANDLE handle);

private:
  HANDLE stdHandle;
};

//颜色表
extern const unsigned short Colors[CTetrisUI::COLORCOUNT];