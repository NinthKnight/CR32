#pragma once
#include <windows.h>

class IPlugin {
public:
    virtual const char* CADGetMenuName() = 0;
    virtual int CADOnLButtonDown(HWND hWnd, int x, int y) = 0;
    virtual int CADOnMouseMove(HWND hWnd, int x, int y) = 0;
    virtual int CADOnLButtonUp(HWND hWnd, int x, int y) = 0;
    virtual int CADOnDraw(HWND hWnd, HDC hdc) = 0;
    virtual int CADSetID(int) = 0;
    virtual int CADGetID() = 0;
    virtual int CADNew() = 0;
    virtual int CADNew2() = 0;
};

typedef IPlugin* (*GET_PLUGIN)();
