#include "stdafx.h"
#include "Sense.h"
#include <stdlib.h>

void CSense::Init()
{
    m_nMapWidth = 10;
    m_nMapHeight = 20;
    
    m_pMap = (char*)malloc(m_nMapWidth * m_nMapHeight);

    //����ǽ��Ҫ��ʼ��

    for (int i = 0; i < m_nMapHeight; i++) {
    
        for (int j = 0; j < m_nMapWidth; j++) {
        
            if (j == 0 || j == m_nMapWidth - 1 || i == m_nMapHeight - 1) {
                m_pMap[i*m_nMapWidth + j] = 1;
            }
            else {
                m_pMap[i*m_nMapWidth + j] = 0;
            }

        }
    }

    //��ʼ������
    m_Block.Init();
    DrawBg();
}


void CSense::DrawBg() {

    for (int i = 0; i < m_nMapHeight; i++) {
        for (int j = 0; j < m_nMapWidth; j++) {
            //��ʾ�ÿ���Ҫ���
            if (m_pMap[i*m_nMapWidth + j] == 0) {
                ShowBg(i, j);
            }
            else if (m_pMap[i*m_nMapWidth + j] == 1) {
                ShowBlock(i, j);
            }


        }
    }
}

//���Ʒ���
void CSense::ShowBlock(int x, int y) {
    WriteChar(x,  // �� 1 ��
        y,  // �� 1 ��
        "  ",
        SetConsoleColor(COLOR_BLUE, // 
            COLOR_BLACK)  // ��ɫ����
        );
}

//���Ʊ���
void CSense::ShowBg(int x, int y) {
    WriteChar(x,  // �� 1 ��
        y,  // �� 1 ��
        "  ",
        SetConsoleColor(COLOR_BLACK, // ��ɫǰ��
            COLOR_WHITE)  // ��ɫ����
        );
}