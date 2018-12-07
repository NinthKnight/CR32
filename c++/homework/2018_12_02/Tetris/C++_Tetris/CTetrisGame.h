#pragma once
#include "CTetrisBlock.h"
#include "CTetrisUI.h"

class CTetrisGame
{
private:
  /*
    ��ͼ�ṹ�� ��ά����
  */
  struct tagGameMap
  {
    int nWidth;
    int nHeight;
    char *maps;
  };

  /*
    �����λ��
  */
  struct tagPos
  {
    int nX;
    int nY;
  };

private:
  //����
  int m_nScore; 
  //��Ϸ�Ƿ����
  bool isGameStart;
  //��������ٶ�
  unsigned int uDropSpeed;

  /*
    ��ͼ���ݱ�ʶ��
  */
  enum emFlags
  {
    SPACE,  //�յ�
    BLOCK,  //����
    BORDER  //�߽�
  };

  /*
    �ƶ�����
  */
  enum emMoveDirection
  {
    MV_UP,
    MV_DOWN,
    MV_LEFT,
    MV_RIGHT
  };

  enum emStatus
  {
    ST_STOP,
    ST_PARALLEL,
    ST_NONE
  };

public:
  /*
    UI������
  */
  CTetrisUI ui;

  /*
    ��Ϸ��ͼ����
  */
  tagGameMap m_tagContainer;

  /*
    ��ǰ����
  */
  CTetrisBlock* m_CurBlock;

  /*
    ��ǰ�����λ��
  */
  tagPos m_CurBlockPos;

  /*
    ��һ������
  */
  CTetrisBlock* m_NextBlock;

public:
  /*
    ���캯��
  */
  CTetrisGame();
  CTetrisGame(int nWidth, int nHeight);

  /*
    ��������
  */
  ~CTetrisGame();

  /*
    ��Ϸ����
  */
  void run();

  /*
    �ƶ�
  */
  emStatus moveBlock(emMoveDirection emDir);

  /*
    ��ʾ
  */
  void display();

  /*
    ��ʾ��Ϣ���
  */
  void displayInfo();

  /*
    ����
  */
  void clearLine();

  /*
    ��Ϸ�Ƿ����
  */
  bool isGameOver();

  /*
  ��ʼ��
  */
  bool initDataAndShowMap();

private:
  /*
    ���
  */
  void clearBlock();

  /*
    ��������
  */
  void createBlock();

  /*
    ����ָ��λ���Ƿ���Ч
  */
  bool isOkPosition(tagPos newPos, CTetrisBlock::tagBlockMap map);
  bool isOkPosition(tagPos newPos);
};