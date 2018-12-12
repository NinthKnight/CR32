#include "stdafx.h"
#include <graphics.h>
#include <conio.h>

int main()
{
    // 初始化绘图窗口
    initgraph(640, 480);

    loadimage(NULL, _T("G:\\123.jpg"));

    // 获取指向显存的指针
    //DWORD* pMem = GetImageBuffer();

    // 按任意键退出
    _getch();
    closegraph();
}