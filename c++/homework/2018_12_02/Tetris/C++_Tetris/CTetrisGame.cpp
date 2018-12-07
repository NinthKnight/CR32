#include "CTetrisGame.h"
#include "TetrisConst.h"
#include <iostream>

/*
  ..
*/
CTetrisGame::CTetrisGame()
{
}

/*
  构造器
*/
CTetrisGame::CTetrisGame(int nWidth, int nHeight)
{
  this->m_CurBlock = nullptr;
  this->m_NextBlock = nullptr;

  //初始分数
  m_nScore = 0;
  //初始速度
  uDropSpeed = GAMESPEED;

  //创建地图
  this->m_tagContainer.maps = new char[nWidth * nHeight]{ 0 };
  this->m_tagContainer.nHeight = nHeight;
  this->m_tagContainer.nWidth = nWidth;

  //创建方块
  createBlock();

  //游戏开始
  isGameStart = true;
}

/*
  释放资源
*/
CTetrisGame::~CTetrisGame()
{
  if (this->m_tagContainer.maps != nullptr)
  {
    delete this->m_tagContainer.maps;
    this->m_tagContainer.maps = nullptr;
  }

  if (this->m_CurBlock != nullptr)
  {
    delete this->m_CurBlock;
    this->m_CurBlock = nullptr;
  }
  
  if (this->m_NextBlock != nullptr)
  {
    delete this->m_NextBlock;
    this->m_NextBlock = nullptr;
  }
}

/*
  创建方块
*/
void CTetrisGame::createBlock()
{
  //地图宽度
  int nWidth = this->m_tagContainer.nWidth;

  if (this->m_NextBlock != NULL)
  {
    //创建一个方块
    if (this->m_CurBlock != nullptr)
    {
      delete this->m_CurBlock;
      this->m_CurBlock = nullptr;
    }
    this->m_CurBlock = m_NextBlock;
    this->m_NextBlock = new CTetrisBlock();
  }
  else
  {
    //第一次
    if (this->m_CurBlock == nullptr)
    {
      this->m_NextBlock = new CTetrisBlock();
      this->m_CurBlock = new CTetrisBlock();
    }
  }

  int nBlockSize = this->m_CurBlock->m_block.nBlockSize;

  //方块位置
  this->m_CurBlockPos.nY = -nBlockSize;
  this->m_CurBlockPos.nX = (nWidth - nBlockSize) / 2;
  //this->m_CurBlockPos.nX = nWidth - 3;

  //展示方块
  displayInfo();

}

bool CTetrisGame::isOkPosition(tagPos newPos, CTetrisBlock::tagBlockMap map)
{
  //方块宽度
  int nBlockSize = map.nBlockSize;
  
  //方块边界
  int nX = newPos.nX;
  int nY = newPos.nY;
  int nBottom = nY + nBlockSize;
  int nRight = nX + nBlockSize;

  //地图宽高
  int nWidth = m_tagContainer.nWidth;
  int nHeight = m_tagContainer.nHeight;

  //地图
  char *pMaps = m_tagContainer.maps;
  char *pBlock = map.block_map;

  //越界
  if (nBottom > nHeight || nX > nWidth)
  {
    return false;
  }

  for (int i = 0, tY = nY; i < nBlockSize; i++, tY++)
  {
    for (int j = 0; j < nBlockSize; j++)
    {
      if (pBlock[i * nBlockSize + j] == BLOCK)
      {
        if (tY < 0)
        {
          continue;
        }
        emFlags emF = (emFlags)pMaps[(nY + i) * nWidth + (nX + j)];
        //底部判断
        if (emF == BORDER || emF == BLOCK)
        {
          //通知上层调用已到底部
          return false;
        }
      }
    }

  }

  return true;
}

bool CTetrisGame::isOkPosition(tagPos newPos)
{
  return isOkPosition(newPos, m_CurBlock->m_block);
}

/*
  地图数据初始化
*/
bool CTetrisGame::initDataAndShowMap()
{
  tagGameMap *pCon = &this->m_tagContainer;
  int nWidth = pCon->nWidth;
  int nHeight = pCon->nHeight;

  for (int i = 0; i < nHeight; i++)
  {
    for (int j = 0; j < nWidth; j++)
    {
      if (j == 0 || j == nWidth - 1 || i == nHeight - 1)
      {
        //数据写入
        pCon->maps[i * nWidth + j] = BORDER;
        //墙体显示
        if (i != 0) //留一行方便判断输赢
        {
          ui.DrawString(nWidth + 15, i - 1, "║", CTetrisUI::WHITE);
          ui.DrawString(j, i - 1, LOG_BORDER, (CTetrisUI::emColor)0);
        }
      }
    }
  }

  return false;
}

/*
  移动方块
    移动返回false表示到底部
*/
CTetrisGame::emStatus CTetrisGame::moveBlock(emMoveDirection emDir)
{
  switch (emDir)
  {
  case CTetrisGame::MV_UP:
  {
    //暂不提供
  }
    break;
  case CTetrisGame::MV_DOWN:
  {
    //给新Pos赋值
    tagPos newPos = m_CurBlockPos;

    //赋予新值
    newPos.nY ++;

    //测试位置有效性
    if (isOkPosition(newPos))
    {
      //如果有效刷新新Pos
      m_CurBlockPos = newPos;
    }
    else
    {
      int nBlockSize = m_CurBlock->m_block.nBlockSize;
      char *pBlock = m_CurBlock->m_block.block_map;
      char *pMaps = m_tagContainer.maps;

      int nX = newPos.nX;
      int nY = newPos.nY;
      int nWidth = m_tagContainer.nWidth;

      if (nY <= 0)
      {
        isGameStart = false;
        return ST_STOP;
      }

      for (int y = 0; y < nBlockSize; y++)
      {
        for (int x = 0; x < nBlockSize; x++)
        {
          int n = pBlock[y * nBlockSize + x];
          if (n == BLOCK)
          {
            pMaps[(nY + y - 1) * nWidth + (nX + x)] = n;
          }
        }
      }
      m_CurBlockPos = newPos;

      return ST_STOP;
    }
  }
    break;
  case CTetrisGame::MV_LEFT:
  {
    //给新Pos赋值
    tagPos newPos = m_CurBlockPos;

    //赋予新值
    newPos.nX--;

    //测试位置有效性
    if (isOkPosition(newPos))
    {
      //如果有效刷新新Pos
      m_CurBlockPos = newPos;
    }

    return ST_PARALLEL;
  }
  case CTetrisGame::MV_RIGHT:
  {
    //给新Pos赋值
    tagPos newPos = m_CurBlockPos;
    //赋予新值
    newPos.nX++;

    //测试位置有效性
    if (isOkPosition(newPos))
    {
      //如果有效刷新新Pos
      m_CurBlockPos = newPos;
    }
  }
    return ST_PARALLEL;
  }

  return ST_NONE;
}

void CTetrisGame::displayInfo()
{
  int nWidth = m_tagContainer.nWidth;
  int nHeight = m_tagContainer.nHeight;
  int nSize = m_NextBlock->m_block.nBlockSize;
  char *block_map = m_NextBlock->m_block.block_map;

  //清空展示区
  for (int i = 0; i < nHeight - 2; i++)
  {
    ui.ClearSpace(nWidth + 1, i, 20);
  }

  //展示方块
  for (int i = 0; i < nSize; i++)
  {
    for (int j = 0; j < nSize; j++)
    {
      int x = m_CurBlockPos.nX + j;
      int y = m_CurBlockPos.nY + i - 1;

      if (block_map[i * nSize + j] == BLOCK)
      {
        //提示
        ui.DrawString((nWidth + 6) + j, 3 + i, LOG_BLOCK, m_NextBlock->getColor());
      }
    }
  }

  int nLeft = nWidth + 2;

  //右边栏显示
  ui.MovePostion(nLeft, 9);
  ui.SetGroundColor(CTetrisUI::YELLOW);
  printf("分数 : %d", m_nScore);

  ui.MovePostion(nLeft, 11);
  ui.SetGroundColor(CTetrisUI::YELLOW);
  printf("速度 : %d", uDropSpeed);

  ui.DrawString(nLeft, 15, "A : 左移  D : 右移", CTetrisUI::PINK);
  ui.DrawString(nLeft, 17, "S : 加速  W : 旋转", CTetrisUI::PINK);
  ui.DrawString(nLeft, 19, "Version : 1.0", CTetrisUI::PINK);
}

/*
  屏幕渲染
*/
void CTetrisGame::display()
{
  int nWidth = m_tagContainer.nWidth;
  int nSize = m_CurBlock->m_block.nBlockSize;
  char *block_map = m_CurBlock->m_block.block_map;

  for (int i = 0; i < nSize; i++)
  {
    for (int j = 0; j < nSize; j++)
    {
      int x = m_CurBlockPos.nX + j;
      int y = m_CurBlockPos.nY + i - 2;

      if (block_map[i * nSize + j] == BLOCK)
      {
        if (x >= 0 && y >= 0)
        {
          ui.DrawString(x, y, LOG_BLOCK, m_CurBlock->getColor());
        }
      }
    }
  }

}

/*
  消行
*/
void CTetrisGame::clearLine()
{
  char *maps = m_tagContainer.maps;
  int nHeight = m_tagContainer.nHeight;
  int nWidth = m_tagContainer.nWidth;

  int nBottom = nHeight - 2;

  int LineNums[HEIGHT] = { 0 };
  int nIndex = HEIGHT - 1;

  //
  for (int i = nBottom; i > 0; i--)
  {
    bool bFlag = true;

    for (int j = 1; j < nWidth - 1; j++)
    {
      if (maps[i * nWidth + j] == SPACE || maps[nBottom * nWidth + j] == BORDER) //底部判断
      {
        bFlag = false;
        break;
      }
    }

    //添加数组
    if (bFlag)
    {
      LineNums[nIndex--] = i;
    }

  }
  //完成消行
  for (int i = nIndex + 1; i < HEIGHT; i++)
  {
    int nSize = nWidth;
    m_nScore = m_nScore + 100;

    //取出行号
    int nNum = LineNums[i];

    for (int k = nNum - 1; k > 0; k--)
    {
      //数据清除
      ::memcpy(&maps[(k + 1) * nWidth], &maps[k * nWidth], nSize);
      //清除一行图像
      ui.CopyLine(k, k - 1, nWidth * 2);
    }

  }
}

/*
  游戏是否结束
*/
bool CTetrisGame::isGameOver()
{
  return !isGameStart;
}

/*
  清屏
*/
void CTetrisGame::clearBlock()
{
  int nSize = m_CurBlock->m_block.nBlockSize;
  char *block_map = m_CurBlock->m_block.block_map;

  for (int i = 0; i < nSize; i++)
  {
    for (int j = 0; j < nSize; j++)
    {
      if (block_map[i * nSize + j] == BLOCK)
      {
        int x = m_CurBlockPos.nX + j;
        int y = m_CurBlockPos.nY + i - 2;

        if (x >= 0 && y >= 0)
        {
          ui.ClearSpace(x, y, 2);
        }
      }
    }
  }
  
}