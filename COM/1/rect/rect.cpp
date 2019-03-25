#include <stdio.h>
#include "../CAD/CAD/CAD.h"

const char* CADGetMenuName()
{
    return "绘制矩形";
}

void CADOnDraw()
{
    printf("绘制矩形中...\n");
}