#include "CTetrisGame.h"
#include <Windows.h>
#include <conio.h>
#include <iostream>
#pragma warning(disable:4996)

/*
  游戏逻辑代码
*/
void CTetrisGame::run()
{
  //键盘下键
  bool isDown = false;
  emStatus mvStatus = ST_NONE;//移动状态

  //游戏主循环
  while (isGameStart)
  {
    //移动方向
    emMoveDirection emMvDir = MV_DOWN; //默认一直下坠

    int nBottom = m_CurBlockPos.nY + m_CurBlock->m_block.nBlockSize;

    //按键检测
    if (_kbhit() && nBottom > 1)
    {
      char ch = 0;
      do
      {
        ch = _getch();
      } while (ch == '\0');

      //清空缓冲区
      while (_kbhit())
      {
        _getch();
      }

      //方块移动判断
      if (ch == 'a' || ch == 'A') //左
      {
        emMvDir = MV_LEFT;
        //isDown = true;
      }
      else if (ch == 'd' || ch == 'D') //右
      {
        emMvDir = MV_RIGHT;
        //isDown = true;
      }
      
      CTetrisBlock::emRotateDirection emRotate = CTetrisBlock::NONE;

      //方块旋转
      if (ch == 'w' || ch == 'W') //左旋转
      {
        emRotate = CTetrisBlock::RO_LEFT;
      }
      else if (ch == 's' || ch == 'S') //下
      {
        isDown = true;
        //emRotate = CTetrisBlock::RO_RIGHT;
      }

      if (emRotate != CTetrisBlock::NONE) //旋转
      {
        int nSize = m_CurBlock->m_block.nBlockSize;
        int nWidth = m_tagContainer.nWidth;

        //旋转之前先清除方块图案
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

        //检查有效性
        if (isOkPosition(m_CurBlockPos, tBlock.m_block))
        {
          //调用方块的旋转函数
          m_CurBlock->rotate(emRotate);
          //直接显示不下坠
          goto SHOW_PROC;
        }
      }

    }

    //移动之前先清除方块图案
    clearBlock();

    //移动
    mvStatus = moveBlock(emMvDir);

    if (mvStatus == ST_STOP)
    { //不能再移动了,就是碰到东西停止了

      //显示
      display();

      //消行并且计分
      clearLine();

      //游戏结束判断
      if (isGameOver())
      {
        ui.GameOver();
        break;
      }
      else
      {
        //重新创建方块
        createBlock();
      }
    }
    else if (mvStatus == ST_PARALLEL)
    {
      
    }

  SHOW_PROC:
    //显示
    display();

    //延时
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