#include <iostream>
#include "CTetrisGame.h"
#include "TetrisConst.h"

int main()
{
  //������Ϸ����
  CTetrisGame GameScene = CTetrisGame(WIDTH, HEIGHT);

  //��ʼ����Ϸ���ݲ���ʾ
  GameScene.initDataAndShowMap();

  //��ʼ��Ϸ
  GameScene.run();

  getchar();
  return 0;
}