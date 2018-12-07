#include "CTetrisGame.h"
#include <Windows.h>
#include <conio.h>
#include <iostream>
#pragma warning(disable:4996)

/*
  ��Ϸ�߼�����
*/
void CTetrisGame::run()
{
  //�����¼�
  bool isDown = false;
  emStatus mvStatus = ST_NONE;//�ƶ�״̬

  //��Ϸ��ѭ��
  while (isGameStart)
  {
    //�ƶ�����
    emMoveDirection emMvDir = MV_DOWN; //Ĭ��һֱ��׹

    int nBottom = m_CurBlockPos.nY + m_CurBlock->m_block.nBlockSize;

    //�������
    if (_kbhit() && nBottom > 1)
    {
      char ch = 0;
      do
      {
        ch = _getch();
      } while (ch == '\0');

      //��ջ�����
      while (_kbhit())
      {
        _getch();
      }

      //�����ƶ��ж�
      if (ch == 'a' || ch == 'A') //��
      {
        emMvDir = MV_LEFT;
        //isDown = true;
      }
      else if (ch == 'd' || ch == 'D') //��
      {
        emMvDir = MV_RIGHT;
        //isDown = true;
      }
      
      CTetrisBlock::emRotateDirection emRotate = CTetrisBlock::NONE;

      //������ת
      if (ch == 'w' || ch == 'W') //����ת
      {
        emRotate = CTetrisBlock::RO_LEFT;
      }
      else if (ch == 's' || ch == 'S') //��
      {
        isDown = true;
        //emRotate = CTetrisBlock::RO_RIGHT;
      }

      if (emRotate != CTetrisBlock::NONE) //��ת
      {
        int nSize = m_CurBlock->m_block.nBlockSize;
        int nWidth = m_tagContainer.nWidth;

        //��ת֮ǰ���������ͼ��
        clearBlock();

        if (m_CurBlockPos.nX <= 0)
        {
          m_CurBlockPos.nX = 1;
        }
        if (m_CurBlockPos.nX >= nWidth - nSize)
        {
          m_CurBlockPos.nX = nWidth - nSize - 1;
        }

        CTetrisBlock tBlock = *m_CurBlock;
        tBlock.rotate(emRotate);

        //�����Ч��
        if (isOkPosition(m_CurBlockPos, tBlock.m_block))
        {
          //���÷������ת����
          m_CurBlock->rotate(emRotate);
          //ֱ����ʾ����׹
          goto SHOW_PROC;
        }
      }

    }

    //�ƶ�֮ǰ���������ͼ��
    clearBlock();

    //�ƶ�
    mvStatus = moveBlock(emMvDir);

    if (mvStatus == ST_STOP)
    { //�������ƶ���,������������ֹͣ��

      //��ʾ
      display();

      //���в��ҼƷ�
      clearLine();

      //��Ϸ�����ж�
      if (isGameOver())
      {
        ui.GameOver();
        break;
      }
      else
      {
        //���´�������
        createBlock();
      }
    }
    else if (mvStatus == ST_PARALLEL)
    {
      
    }

  SHOW_PROC:
    //��ʾ
    display();

    //��ʱ
    if (isDown)
    {
      Sleep(30);
      isDown = false;
    }
    else
    {
      Sleep(uDropSpeed);
    }
  }

}