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
  ������
*/
CTetrisGame::CTetrisGame(int nWidth, int nHeight)
{
  this->m_CurBlock = nullptr;
  this->m_NextBlock = nullptr;

  //��ʼ����
  m_nScore = 0;
  //��ʼ�ٶ�
  uDropSpeed = GAMESPEED;

  //������ͼ
  this->m_tagContainer.maps = new char[nWidth * nHeight]{ 0 };
  this->m_tagContainer.nHeight = nHeight;
  this->m_tagContainer.nWidth = nWidth;

  //��������
  createBlock();

  //��Ϸ��ʼ
  isGameStart = true;
}

/*
  �ͷ���Դ
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
  ��������
*/
void CTetrisGame::createBlock()
{
  //��ͼ���
  int nWidth = this->m_tagContainer.nWidth;

  if (this->m_NextBlock != NULL)
  {
    //����һ������
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
    //��һ��
    if (this->m_CurBlock == nullptr)
    {
      this->m_NextBlock = new CTetrisBlock();
      this->m_CurBlock = new CTetrisBlock();
    }
  }

  int nBlockSize = this->m_CurBlock->m_block.nBlockSize;

  //����λ��
  this->m_CurBlockPos.nY = -nBlockSize;
  this->m_CurBlockPos.nX = (nWidth - nBlockSize) / 2;
  //this->m_CurBlockPos.nX = nWidth - 3;

  //չʾ����
  displayInfo();

}

bool CTetrisGame::isOkPosition(tagPos newPos, CTetrisBlock::tagBlockMap map)
{
  //������
  int nBlockSize = map.nBlockSize;
  
  //����߽�
  int nX = newPos.nX;
  int nY = newPos.nY;
  int nBottom = nY + nBlockSize;
  int nRight = nX + nBlockSize;

  //��ͼ���
  int nWidth = m_tagContainer.nWidth;
  int nHeight = m_tagContainer.nHeight;

  //��ͼ
  char *pMaps = m_tagContainer.maps;
  char *pBlock = map.block_map;

  //Խ��
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
        //�ײ��ж�
        if (emF == BORDER || emF == BLOCK)
        {
          //֪ͨ�ϲ�����ѵ��ײ�
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
  ��ͼ���ݳ�ʼ��
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
        //����д��
        pCon->maps[i * nWidth + j] = BORDER;
        //ǽ����ʾ
        if (i != 0) //��һ�з����ж���Ӯ
        {
          ui.DrawString(nWidth + 15, i - 1, "�U", CTetrisUI::WHITE);
          ui.DrawString(j, i - 1, LOG_BORDER, (CTetrisUI::emColor)0);
        }
      }
    }
  }

  return false;
}

/*
  �ƶ�����
    �ƶ�����false��ʾ���ײ�
*/
CTetrisGame::emStatus CTetrisGame::moveBlock(emMoveDirection emDir)
{
  switch (emDir)
  {
  case CTetrisGame::MV_UP:
  {
    //�ݲ��ṩ
  }
    break;
  case CTetrisGame::MV_DOWN:
  {
    //����Pos��ֵ
    tagPos newPos = m_CurBlockPos;

    //������ֵ
    newPos.nY ++;

    //����λ����Ч��
    if (isOkPosition(newPos))
    {
      //�����Чˢ����Pos
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
    //����Pos��ֵ
    tagPos newPos = m_CurBlockPos;

    //������ֵ
    newPos.nX--;

    //����λ����Ч��
    if (isOkPosition(newPos))
    {
      //�����Чˢ����Pos
      m_CurBlockPos = newPos;
    }

    return ST_PARALLEL;
  }
  case CTetrisGame::MV_RIGHT:
  {
    //����Pos��ֵ
    tagPos newPos = m_CurBlockPos;
    //������ֵ
    newPos.nX++;

    //����λ����Ч��
    if (isOkPosition(newPos))
    {
      //�����Чˢ����Pos
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

  //���չʾ��
  for (int i = 0; i < nHeight - 2; i++)
  {
    ui.ClearSpace(nWidth + 1, i, 20);
  }

  //չʾ����
  for (int i = 0; i < nSize; i++)
  {
    for (int j = 0; j < nSize; j++)
    {
      int x = m_CurBlockPos.nX + j;
      int y = m_CurBlockPos.nY + i - 1;

      if (block_map[i * nSize + j] == BLOCK)
      {
        //��ʾ
        ui.DrawString((nWidth + 6) + j, 3 + i, LOG_BLOCK, m_NextBlock->getColor());
      }
    }
  }

  int nLeft = nWidth + 2;

  //�ұ�����ʾ
  ui.MovePostion(nLeft, 9);
  ui.SetGroundColor(CTetrisUI::YELLOW);
  printf("���� : %d", m_nScore);

  ui.MovePostion(nLeft, 11);
  ui.SetGroundColor(CTetrisUI::YELLOW);
  printf("�ٶ� : %d", uDropSpeed);

  ui.DrawString(nLeft, 15, "A : ����  D : ����", CTetrisUI::PINK);
  ui.DrawString(nLeft, 17, "S : ����  W : ��ת", CTetrisUI::PINK);
  ui.DrawString(nLeft, 19, "Version : 1.0", CTetrisUI::PINK);
}

/*
  ��Ļ��Ⱦ
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
  ����
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
      if (maps[i * nWidth + j] == SPACE || maps[nBottom * nWidth + j] == BORDER) //�ײ��ж�
      {
        bFlag = false;
        break;
      }
    }

    //�������
    if (bFlag)
    {
      LineNums[nIndex--] = i;
    }

  }
  //�������
  for (int i = nIndex + 1; i < HEIGHT; i++)
  {
    int nSize = nWidth;
    m_nScore = m_nScore + 100;

    //ȡ���к�
    int nNum = LineNums[i];

    for (int k = nNum - 1; k > 0; k--)
    {
      //�������
      ::memcpy(&maps[(k + 1) * nWidth], &maps[k * nWidth], nSize);
      //���һ��ͼ��
      ui.CopyLine(k, k - 1, nWidth * 2);
    }

  }
}

/*
  ��Ϸ�Ƿ����
*/
bool CTetrisGame::isGameOver()
{
  return !isGameStart;
}

/*
  ����
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