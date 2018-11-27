#include "stdafx.h"
#include "Sense.h"
#include <stdlib.h>

void CSense::Init()
{
    m_nMapWidth = 10;
    m_nMapHeight = 20;
    
    m_pMap = (char*)malloc(m_nMapWidth * m_nMapHeight);

    //背景墙需要初始化

    for (int i = 0; i < m_nMapHeight; i++) {
    
        for (int j = 0; j < m_nMapWidth; j++) {
        
            if (j == 0 || j == m_nMapWidth - 1 || i == m_nMapHeight - 1) {
                m_pMap[i*m_nMapWidth + j] = 1;
            }
            else {
                m_pMap[i*m_nMapWidth + j] = 0;
            }

        }
    }

    //初始化方块
    m_Block.Init();
    DrawBg();
}


void CSense::DrawBg() {

    for (int i = 0; i < m_nMapHeight; i++) {
        for (int j = 0; j < m_nMapWidth; j++) {
            //表示该块需要清除
            if (m_pMap[i*m_nMapWidth + j] == 0) {
                ShowBg(i, j);
            }
            else if (m_pMap[i*m_nMapWidth + j] == 1) {
                ShowBlock(i, j);
            }


        }
    }
}

//绘制方块
void CSense::ShowBlock(int x, int y) {
    WriteChar(x,  // 第 1 行
        y,  // 第 1 列
        "  ",
        SetConsoleColor(COLOR_BLUE, // 
            COLOR_BLACK)  // 白色背景
        );
}

//绘制背景
void CSense::ShowBg(int x, int y) {
    WriteChar(x,  // 第 1 行
        y,  // 第 1 列
        "  ",
        SetConsoleColor(COLOR_BLACK, // 黑色前景
            COLOR_WHITE)  // 白色背景
        );
}