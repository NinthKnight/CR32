#include <iostream>
#include "CTetrisGame.h"
#include "TetrisConst.h"

int main()
{
  //创建游戏场景
  CTetrisGame GameScene = CTetrisGame(WIDTH, HEIGHT);

  //初始化游戏数据并显示
  GameScene.initDataAndShowMap();

  //开始游戏
  GameScene.run();

  getchar();
  return 0;
}