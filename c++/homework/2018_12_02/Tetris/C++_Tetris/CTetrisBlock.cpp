#include "CTetrisBlock.h"
#include <string.h>
#include <iostream>
#include <time.h>

/*
  构造
*/
CTetrisBlock::CTetrisBlock()
{
  //初始化0
  this->m_block = { 0 };
  this->create();
}
CTetrisBlock::CTetrisBlock(tagBlockMap block_map, CTetrisUI::emColor eColor) : m_block(block_map), m_emColor(eColor){
}

CTetrisBlock::CTetrisBlock(CTetrisBlock & block)
{
  int nSize = block.m_block.nBlockSize;
  m_block.nBlockSize = nSize;

  m_block.block_map = new char[nSize * nSize]{ 0 };
  memcpy(m_block.block_map, block.m_block.block_map, nSize * nSize);

  m_emColor = block.m_emColor;
}

CTetrisBlock::~CTetrisBlock()
{
  this->destroy();
}

/*
  创建指定类型颜色的方块
*/
bool CTetrisBlock::create(tagBlockMap block_map, CTetrisUI::emColor emColor)
{
  if (this->m_block.block_map != NULL)
  {
    delete this->m_block.block_map;
    this->m_block.block_map = NULL;
  }

  ::memcpy(&this->m_block, &block_map, sizeof(this->m_block));

  this->m_emColor = emColor;

  return true;
}

/*
  创建随机类型随机颜色
*/
bool CTetrisBlock::create()
{
  //初始化随机数种子
  srand((unsigned int)time(NULL));

  //随机一种图案
  int nType = rand() % BLOCKCOUNT;
  //int nType = 5;

  //大小
  int nMapSize = g_Block_sizes[nType];

  //申请空间
  if (this->m_block.block_map != NULL)
  {
    delete this->m_block.block_map;
    this->m_block.block_map = NULL;
  }
  this->m_block.block_map = new char[nMapSize * nMapSize]{ 0 };
  if (this->m_block.block_map == NULL)
  {
    return false;
  }

  //拷贝
  for (int i = 0; i < nMapSize; i++)
  {
    for (int j = 0; j < nMapSize; j++)
    {
      this->m_block.block_map[i * nMapSize + j] = g_Blocks[nType][i][j];
    }
  }

  this->m_block.nBlockSize = nMapSize;

  //随机颜色
  this->m_emColor = (CTetrisUI::emColor) (rand() % CTetrisUI::COLORCOUNT);

  return true;
}

/*
  图形旋转
*/
void CTetrisBlock::rotate(emRotateDirection emDir)
{
  //地图大小
  int nMapSize = this->m_block.nBlockSize;

  //临时空间
  char *ary = (char *) new char[nMapSize * nMapSize]{ 0 };
  if (ary == NULL)
  {
    goto EXIT_PROC;
  }

  if (emDir == RO_LEFT)
  {
    //左旋转
    for (int i = 0; i < nMapSize; i++)
    {
      for (int j = 0; j < nMapSize; j++)
      {
        //顺时针旋转,列跟着行变化
        ary[i * nMapSize + j] = this->m_block.block_map[j * nMapSize + (nMapSize - 1 - i)];
      }
    }

    //赋值给m_block_map
    ::memcpy(this->m_block.block_map, ary, nMapSize * nMapSize);
  }
  else if (emDir == RO_RIGHT)
  {
    //右旋转
    for (int i = 0; i < nMapSize; i++)
    {
      for (int j = 0; j < nMapSize; j++)
      {
        //顺时针旋转,行跟着列变化
        ary[i * nMapSize + j] = this->m_block.block_map[(nMapSize - 1 - j) * nMapSize + i];
      }
    }

    //赋值给m_block_map
    ::memcpy(this->m_block.block_map, ary, nMapSize * nMapSize);
  }

EXIT_PROC:
  if (ary != NULL)
  {
    delete ary;
  }

  return;
}

/*
  显示信息
*/
void CTetrisBlock::display()
{
  using namespace std;

  //地图大小
  int nMapSize = this->m_block.nBlockSize;

  cout << endl;
  for (int i = 0; i < nMapSize; i++)
  {
    for (int j = 0; j < nMapSize; j++)
    {
      cout << (int)this->m_block.block_map[i * nMapSize + j] << " ";
    }
    cout << endl;
  }
}

/*
  销毁
*/
void CTetrisBlock::destroy()
{
  //销毁方块内存
  if (this->m_block.block_map != NULL)
  {
    delete this->m_block.block_map;
    this->m_block.block_map = NULL;
  }
}

/*
  获取颜色
*/
CTetrisUI::emColor CTetrisBlock::getColor()
{
  return this->m_emColor;
}

/*
  设置颜色
*/
void CTetrisBlock::setColor(CTetrisUI::emColor eColor)
{
  this->m_emColor = eColor;
}
