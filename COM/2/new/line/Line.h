#pragma once
#include "F:\COM\2\new\CAD\CAD\plugin.h"
class CLine : public IPlugin
{
public:
    CLine();
    virtual ~CLine();

    // 通过 IPlugin 继承
    virtual const char * CADGetMenuName() override;
    virtual int CADOnLButtonDown(HWND hWnd, int x, int y) override;
    virtual int CADOnMouseMove(HWND hWnd, int x, int y) override;
    virtual int CADOnLButtonUp(HWND hWnd, int x, int y) override;
    virtual int CADOnDraw(HWND hWnd, HDC hdc) override;
    virtual int CADSetID(int) override;
    virtual int CADGetID() override;
    virtual int CADNew() override;

    // 通过 IPlugin 继承
    virtual int CADNew2() override;
private:
    int m_ID;
    POINT m_ptBegin;
    POINT m_ptEnd;
};

