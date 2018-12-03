#pragma once
#include "TetrisConst.h"
#include "CTetrisUI.h"

/*
  方块类
*/
class CTetrisBlock
{
public: //常量表
 
  //旋转方向
  enum emRotateDirection
  {
    NONE, //无效值
    RO_LEFT, //左旋
    RO_RIGHT //右旋
  };

  //移动方向
  enum emMoveDirection
  {
    MV_UP,
    MV_DOWN,
    MV_LEFT,
    MV_RIGHT
  };

  //方块
  struct tagBlockMap
  {
    int nBlockSize;
    char *block_map;
  };

private: //私有属性
  //每个方块的颜色
  CTetrisUI::emColor m_emColor;

public: 
  //每一个方块的图形
  tagBlockMap m_block;

//----------------------------- 接口 -------------------------------

  //构造函数
  CTetrisBlock();
  CTetrisBlock(tagBlockMap block_map, CTetrisUI::emColor eColor);
  CTetrisBlock(CTetrisBlock & block);

  //析构
  ~CTetrisBlock();

  //创建一个指定图形指定颜色的方块
  bool create(tagBlockMap block_map, CTetrisUI::emColor eColor);

  //创建一个随机图形随机颜色的方块
  bool create();
  
  //旋转
  void rotate(emRotateDirection emDir);

  //此功能只能打印block_map表,显示功能并非此对象所拥有
  void display();

  //销毁
  void destroy();

  //get
  CTetrisUI::emColor getColor();

  //set
  void setColor(CTetrisUI::emColor eColor);
};