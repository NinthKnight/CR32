#pragma once
#include "TetrisConst.h"
#include "CTetrisUI.h"

/*
  ������
*/
class CTetrisBlock
{
public: //������
 
  //��ת����
  enum emRotateDirection
  {
    NONE, //��Чֵ
    RO_LEFT, //����
    RO_RIGHT //����
  };

  //�ƶ�����
  enum emMoveDirection
  {
    MV_UP,
    MV_DOWN,
    MV_LEFT,
    MV_RIGHT
  };

  //����
  struct tagBlockMap
  {
    int nBlockSize;
    char *block_map;
  };

private: //˽������
  //ÿ���������ɫ
  CTetrisUI::emColor m_emColor;

public: 
  //ÿһ�������ͼ��
  tagBlockMap m_block;

//----------------------------- �ӿ� -------------------------------

  //���캯��
  CTetrisBlock();
  CTetrisBlock(tagBlockMap block_map, CTetrisUI::emColor eColor);
  CTetrisBlock(CTetrisBlock & block);

  //����
  ~CTetrisBlock();

  //����һ��ָ��ͼ��ָ����ɫ�ķ���
  bool create(tagBlockMap block_map, CTetrisUI::emColor eColor);

  //����һ�����ͼ�������ɫ�ķ���
  bool create();
  
  //��ת
  void rotate(emRotateDirection emDir);

  //�˹���ֻ�ܴ�ӡblock_map��,��ʾ���ܲ��Ǵ˶�����ӵ��
  void display();

  //����
  void destroy();

  //get
  CTetrisUI::emColor getColor();

  //set
  void setColor(CTetrisUI::emColor eColor);
};