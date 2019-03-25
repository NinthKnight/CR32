#include <stdio.h>
#include "../CAD/CAD/plugin.h"
#include <windows.h>
#include "Line.h"

CLine g_obj;

IPlugin* GetPlugin() {
    return &g_obj;
    return NULL;
}

CLine::CLine()
    : m_ID(0)
{
}


CLine::~CLine()
{
}

const char * CLine::CADGetMenuName()
{
    return "Line(&L)";
}

int CLine::CADOnLButtonDown(HWND hWnd, int x, int y)
{
    m_ptBegin.x = x;
    m_ptBegin.y = y;
    return 0;
}

int CLine::CADOnMouseMove(HWND hWnd, int x, int y)
{
    m_ptEnd.x = x;
    m_ptEnd.y = y;

    return 0;
}

int CLine::CADOnLButtonUp(HWND hWnd, int x, int y)
{
    m_ptEnd.x = x;
    m_ptEnd.y = y;


    HDC hdc = GetDC(hWnd);
    MoveToEx(hdc, m_ptBegin.x, m_ptBegin.y, 0);
    LineTo(hdc, m_ptEnd.x, m_ptEnd.y);
    return 0;
}

int CLine::CADOnDraw(HWND hWnd, HDC hdc)
{
    MessageBox(NULL, "CLine::CADOnDraw", nullptr, MB_OK);
    return 0;
}

int CLine::CADSetID(int id)
{
    m_ID = id;
    return 0;
}

int CLine::CADGetID()
{
    return m_ID;
}

int CLine::CADNew()
{
    return 0;
}

int CLine::CADNew2()
{
    return 0;
}



