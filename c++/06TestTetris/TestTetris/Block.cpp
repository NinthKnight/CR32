#include "stdafx.h"
#include "Block.h"
#include <stdlib.h>
#include <stdio.h>


void CBlock::Init()
{
    SetRadom();
    SetShape(m_Type);
}

void CBlock::LeftRotate()
{
    int coords[4][2];
    memcpy(coords, m_coords, sizeof(coords));

    for (int i = 0; i < 4; ++i) {
        SetX(i, coords[i][1]);
        SetY(i, -coords[i][0]);
    }

}

void CBlock::RightRotate()
{
    int coords[4][2];
    memcpy(coords, m_coords, sizeof(coords));

    for (int i = 0; i < 4; ++i) {
        SetX(i, -coords[i][1]);
        SetY(i, coords[i][0]);
    }
}

//旋转方块


void CBlock::SetRadom()
{
    //产生随机的类型
    m_Type = (emBlockType)(rand() % 7 + 1);
    //m_Type = LineShape;
}

void CBlock::SetShape(emBlockType nType)
{
    static const int coordsTable[8][4][2] = {
        { { 0, 0 },{ 0, 0 },{ 0, 0 },{ 0, 0 } },
        { { 0, -1 },{ 0, 0 },{ -1, 0 },{ -1, 1 } },
        { { 0, -1 },{ 0, 0 },{ 1, 0 },{ 1, 1 } },
        { { 0, -1 },{ 0, 0 },{ 0, 1 },{ 0, 2 } },
        { { -1, 0 },{ 0, 0 },{ 1, 0 },{ 0, 1 } },
        { { 0, 0 },{ 1, 0 },{ 0, 1 },{ 1, 1 } },
        { { -1, -1 },{ 0, -1 },{ 0, 0 },{ 0, 1 } },
        { { 1, -1 },{ 0, -1 },{ 0, 0 },{ 0, 1 } }
    };

    for (int i = 0; i < 4; i++) {
        m_coords[i][0] = coordsTable[nType][i][0];
        m_coords[i][1] = coordsTable[nType][i][1];
    }
}
