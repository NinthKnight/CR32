#include <stdio.h>
#include "../CAD/CAD/CAD.h"
#include <windows.h>

const char* CADGetMenuName()
{

    return "����ֱ��";
}

 void CADOnDraw() {
    printf("����ֱ��...\n");
    HWND hDesk = GetDesktopWindow();
    HDC hdc = GetDC(hDesk);
    MoveToEx(hdc, 0, 0, NULL);
    LineTo(hdc, 200, 200);
}