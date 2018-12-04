#include "stdafx.h"
#include "Tank.h"


CTank::CTank(int nType, int nRotate, int nCurX, int nCurY){

    m_nRotate = nRotate;
    m_nCurX = nCurX;
    m_nCurY = nCurY;
    m_nType = nType;
}


CTank::~CTank()
{

}

void CTank::OnUp()
{
    m_nCurY -= 2;
}

void CTank::OnDown()
{
    m_nCurY += 2;
}

void CTank::OnLeft()
{
    m_nCurX -= 2;
}

void CTank::OnRight()
{
    m_nCurX += 2;
}
