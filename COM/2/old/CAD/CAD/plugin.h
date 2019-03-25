#pragma once
#include <windows.h>

#define PLUGIN_OK      0
#define PLUGIN_ERROR   1

typedef int (*IHII)(HWND hWnd, int x, int y);
typedef const char* (*PCV)();
typedef int (*IHH)(HWND hWnd, HDC hdc);
typedef int (*II)(int);
typedef int (*IV)();

typedef struct _Plugin {
    PCV        CADGetMenuName;
    IHII       CADOnLButtonDown;
    IHII       CADOnMouseMove;
    IHII       CADOnLButtonUp;
    IHH        CADOnDraw;
    II         CADSetID;
    IV         CADGetID;
}Plugin;

typedef Plugin* (*GET_PLUGIN)();

Plugin* GetPlugin();  //µ¼³ö




const char* CADGetMenuName();
int CADOnLButtonDown(HWND hWnd, int x, int y);
int CADOnMouseMove(HWND hWnd, int x, int y);
int CADOnLButtonUp(HWND hWnd, int x, int y);
int CADOnDraw(HWND hWnd, HDC hdc);
int CADSetID(int);
int CADGetID();
