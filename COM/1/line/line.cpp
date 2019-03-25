#include <stdio.h>
#include "../CAD/CAD/CAD.h"
#include <windows.h>

const char* CADGetMenuName()
{

    return "绘制直线";
}

 void CADOnDraw() {
    printf("绘制直线...\n");
    HWND hDesk = GetDesktopWindow();
    HDC hdc = GetDC(hDesk);
    MoveToEx(hdc, 0, 0, NULL);
    LineTo(hdc, 200, 200);
}