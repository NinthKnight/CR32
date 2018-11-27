#include <iostream>
/*
针对俄罗斯方块游戏，对方块对象进行封装，实现包括但是不限于
以下的功能：移动，旋转，显示，创建新方块
（指定类型或随机类型两种方法）
*/

/*
  游戏地图
*/
struct tagGameMap
{
  int nWidth;
  int nHeight;
  int *maps;
};

/*
  方块类,此类的对象表示一个方块
    一个方块的属性有,他的图案也就是二维数组数据,颜色
*/
class CTetrisBlock
{
private:
  //枚举常量
  enum { BLOCKSIZE = 4 }; //方块大小

  //每个方块的颜色
  int nColor;

public:
  //每一个方块的图形
  int block_map[BLOCKSIZE][BLOCKSIZE];

  //颜色值
  enum eColor 
  { 
    RED, 
    GREEN, 
    BLUE 
  };

  //旋转角度
  enum eRotateAngle
  {
    RO_LEFT, //向左旋转
    RO_RIGHT //向右旋转
  };

  //移动方向
  enum eMoveDirection
  {
    MV_UP,
    MV_DOWN,
    MV_LEFT,
    MV_RIGHT
  };

 /*--------------------接口----------------------*/

  //移动
  bool move(tagGameMap *game_map, eMoveDirection eDirection, int nStep);

  //旋转
  bool rotate(eRotateAngle eAngle);

  //此功能只能打印block_map表,显示功能并非此对象所拥有
  void display();

  //创建一个指定图形指定颜色的方块
  bool create(int block_map[BLOCKSIZE][BLOCKSIZE], int nColor);

  //创建一个随机图形随机颜色的方块
  bool create();
};

using namespace std;
int main()
{
  
  return 0;
}