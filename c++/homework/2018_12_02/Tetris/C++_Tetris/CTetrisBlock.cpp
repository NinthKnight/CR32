#include "CTetrisBlock.h"
#include <string.h>
#include <iostream>
#include <time.h>

/*
  ����
*/
CTetrisBlock::CTetrisBlock()
{
  //��ʼ��0
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
  ����ָ��������ɫ�ķ���
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
  ����������������ɫ
*/
bool CTetrisBlock::create()
{
  //��ʼ�����������
  srand((unsigned int)time(NULL));

  //���һ��ͼ��
  int nType = rand() % BLOCKCOUNT;
  //int nType = 5;

  //��С
  int nMapSize = g_Block_sizes[nType];

  //����ռ�
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

  //����
  for (int i = 0; i < nMapSize; i++)
  {
    for (int j = 0; j < nMapSize; j++)
    {
      this->m_block.block_map[i * nMapSize + j] = g_Blocks[nType][i][j];
    }
  }

  this->m_block.nBlockSize = nMapSize;

  //�����ɫ
  this->m_emColor = (CTetrisUI::emColor) (rand() % CTetrisUI::COLORCOUNT);

  return true;
}

/*
  ͼ����ת
*/
void CTetrisBlock::rotate(emRotateDirection emDir)
{
  //��ͼ��С
  int nMapSize = this->m_block.nBlockSize;

  //��ʱ�ռ�
  char *ary = (char *) new char[nMapSize * nMapSize]{ 0 };
  if (ary == NULL)
  {
    goto EXIT_PROC;
  }

  if (emDir == RO_LEFT)
  {
    //����ת
    for (int i = 0; i < nMapSize; i++)
    {
      for (int j = 0; j < nMapSize; j++)
      {
        //˳ʱ����ת,�и����б仯
        ary[i * nMapSize + j] = this->m_block.block_map[j * nMapSize + (nMapSize - 1 - i)];
      }
    }

    //��ֵ��m_block_map
    ::memcpy(this->m_block.block_map, ary, nMapSize * nMapSize);
  }
  else if (emDir == RO_RIGHT)
  {
    //����ת
    for (int i = 0; i < nMapSize; i++)
    {
      for (int j = 0; j < nMapSize; j++)
      {
        //˳ʱ����ת,�и����б仯
        ary[i * nMapSize + j] = this->m_block.block_map[(nMapSize - 1 - j) * nMapSize + i];
      }
    }

    //��ֵ��m_block_map
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
  ��ʾ��Ϣ
*/
void CTetrisBlock::display()
{
  using namespace std;

  //��ͼ��С
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
  ����
*/
void CTetrisBlock::destroy()
{
  //���ٷ����ڴ�
  if (this->m_block.block_map != NULL)
  {
    delete this->m_block.block_map;
    this->m_block.block_map = NULL;
  }
}

/*
  ��ȡ��ɫ
*/
CTetrisUI::emColor CTetrisBlock::getColor()
{
  return this->m_emColor;
}

/*
  ������ɫ
*/
void CTetrisBlock::setColor(CTetrisUI::emColor eColor)
{
  this->m_emColor = eColor;
}
