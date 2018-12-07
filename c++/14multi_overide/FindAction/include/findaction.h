#pragma once

// 地图大小
#define MAPROW  31  // 行
#define MAPCOL  28  // 列

class CPostion;

/*
* 寻路算法
* 
* eg: FindAction(pMap, (5, 5), (10, 10), pCrashElement, 2);
*
* pMap:             地图二维数组指针
* srcPos:           起始坐标
* dstPos:           目标坐标
* pCarshElement:    会发生碰撞元素的数组
* nCarshElementNum: 数组元素个数（默认为1）
*
* 注：在吃豆人游戏模式中对于鬼而言，
*     只有墙是不可穿越的，
*     但为了算法的可扩展性采用了数组的形式，
*     从而实现地图中增加新的鬼不可穿越元素
*     算法无需修改的目的。
*     其实也可以采用位运算的方式，
*     但这样对地图元素定义有要求，
*     所以不采用。
*
*     对于传入目标坐标合法性检查，
*     在传入目标坐标不合法的情况下，
*     默认将目标向下移动一格（在吃豆人地图中不会有错），
*     也可根据需求在实现代码中调整为返回 -1 或其他处理方法
*/
int FindAction(const int (*pMap)[MAPCOL] ,
               CPostion srcPos ,
               CPostion dstPos ,
               int *pCrashElement ,
               int nCrashElementNum = 1
               );

// 方向
enum emAction
{
  actUp = 0,
  actDown,
  actLeft,
  actRight
};


// x, y 坐标点
enum emPostion
{
  posRow = 0,
  posCol
};

// 坐标类，用于简化寻路算法
class CPostion
{
public:
  CPostion();
  CPostion(int nRow , int nCol);
  CPostion(CPostion& obj);
  ~CPostion();
  // 获取对应横纵坐标
  int& operator[](int nIndex);
  // 坐标赋值
  CPostion& operator=(CPostion& obj);
  // 将两个坐标相加（直接相加）
  CPostion operator+(CPostion& obj);
  // 获取两个坐标差（横竖差坐标的差，可以是负值）
  CPostion operator-(CPostion& obj);
  // 将坐标与数字相乘
  CPostion operator*(int nNum);
  // 判断坐标是否相等
  int operator==(CPostion& obj);
  int operator!=(CPostion& obj);
  // 修正坐标（防止越界）
  void amend();
  // 设置坐标
  void set(int nRow , int nCol);
  // 获取这个方向下个坐标
  CPostion getActionPostion(int nAction);
  // 根据方向修改坐标
  void changePostion(int nAction);

private:
  int m_nRow;
  int m_nCol;
};


/*
* 简单的碰撞检测
* nMapElement:      地图上的元素
* pCarshElement:    会发生碰撞元素的数组
* nCarshElementNum: 数组元素个数
*
* 注：在吃豆人游戏模式中对于鬼而言，
*     只有墙是不可穿越的，
*     但为了算法的可扩展性采用了数组的形式，
*     从而实现地图中增加新的鬼不可穿越元素
*     算法无需修改的目的。
*     其实也可以采用位运算的方式，
*     但这样对地图元素定义有要求，
*     所以不采用。
*/
bool ThisPointIsCarsh(int nMapElement ,
                      int* pCarshElement ,
                      int nCarshElementNum);