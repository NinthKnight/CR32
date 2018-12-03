#pragma once
#include "CTetrisBlock.h"
#include "CTetrisUI.h"

class CTetrisGame
{
private:
  /*
    地图结构体 二维数组
  */
  struct tagGameMap
  {
    int nWidth;
    int nHeight;
    char *maps;
  };

  /*
    方块的位置
  */
  struct tagPos
  {
    int nX;
    int nY;
  };

private:
  //分数
  int m_nScore; 
  //游戏是否结束
  bool isGameStart;
  //方块掉落速度
  unsigned int uDropSpeed;

  /*
    地图数据标识符
  */
  enum emFlags
  {
    SPACE,  //空地
    BLOCK,  //方块
    BORDER  //边界
  };

  /*
    移动方向
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
    UI处理类
  */
  CTetrisUI ui;

  /*
    游戏地图容器
  */
  tagGameMap m_tagContainer;

  /*
    当前方块
  */
  CTetrisBlock* m_CurBlock;

  /*
    当前方块的位置
  */
  tagPos m_CurBlockPos;

  /*
    下一个方块
  */
  CTetrisBlock* m_NextBlock;

public:
  /*
    构造函数
  */
  CTetrisGame();
  CTetrisGame(int nWidth, int nHeight);

  /*
    析构函数
  */
  ~CTetrisGame();

  /*
    游戏运行
  */
  void run();

  /*
    移动
  */
  emStatus moveBlock(emMoveDirection emDir);

  /*
    显示
  */
  void display();

  /*
    显示信息面板
  */
  void displayInfo();

  /*
    消行
  */
  void clearLine();

  /*
    游戏是否结束
  */
  bool isGameOver();

  /*
  初始化
  */
  bool initDataAndShowMap();

private:
  /*
    清除
  */
  void clearBlock();

  /*
    创建方块
  */
  void createBlock();

  /*
    测试指定位置是否有效
  */
  bool isOkPosition(tagPos newPos, CTetrisBlock::tagBlockMap map);
  bool isOkPosition(tagPos newPos);
};