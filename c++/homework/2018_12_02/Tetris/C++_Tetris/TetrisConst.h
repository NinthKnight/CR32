#pragma once
#define BLOCKCOUNT  8     //方块种类数量

#define WIDTH       22    //地图宽高
#define HEIGHT      26
#define GAMESPEED   250   //方块掉落速度

//图像log
#define LOG_BORDER  "■"
#define LOG_BLOCK   "□"

extern char g_Blocks[BLOCKCOUNT][4][4];
extern char g_Block_sizes[BLOCKCOUNT];