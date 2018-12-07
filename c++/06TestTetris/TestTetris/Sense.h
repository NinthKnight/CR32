#pragma once
#include "Block.h"
#include "setdisplay.h"

class CSense
{
public:
    void Init();

    void DrawBg();

    void ShowBlock(int x, int y);
    void ShowBg(int x, int y);


private:
    char* m_pMap;
    int m_nMapWidth;
    int m_nMapHeight;

    CBlock m_Block;
    int  m_nCurX;
    int m_nCurY;

};

