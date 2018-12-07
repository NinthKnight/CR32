#include "findaction.h"

/**************************************************
* 寻路算法 - 广度搜索遗忘算法（李家诚的算法）
*
* 该算法用于动点到动点的寻路，
* 是一种实时算法，每次只能获取下一步该向那个方向走。
*
* 由于整个算法的目的是为了知道下一步该向那个方向走，
* 所以所有的操作都围绕保存正确的方向为主，
* 因此也不需要保存走过的路径。
* 
* 在小而复杂的地图上，
* 这个算法的效率是远远高于 A-Star 算法。
* 因为 A-Star 算法是用于动点到静点的寻路，
* 并且在寻路过程中不断保存整条路径；
* 其次大部分容易理解的 A-Star 算法都是采用递归方法实现，
* 在效率上有很大问题，
* 而该算法的实现采用的是迭代的方式。
* 因此在吃豆人这个游戏场景中，该算法优势更大。
*
* 该算法缺点：
*     如果给了一个不可能到达的目标点（被四面墙围住的点），
*     就会死循环！
*
* 最大效率使用方法：
*     在吃豆人的游戏模式中，鬼只有在路口时才会改变方向，
*     因此，只在路口调用该算法来获得方向会使游戏效率提高
*     但有一个现实问题：每在路口调用时所带来的开销可能
*     会产生非常非常细微的卡顿感，这主要取决于如何设计
*     游戏逻辑，设计的成功是没有卡顿感的
**************************************************/


/******************* 算法伪代码 ********************
// 算法主要逻辑，省掉了合法性检查、移动坐标、碰撞检测等
方向 FindAction(x0, y0, x1, y1){
		int 最优方向 = NONE
		先记录原来目标,x0, y0
		while(true){
			便利容器{
				if(定位到目标){
					return 方向
				}
				else if(能向上移动){
					下个状态添加进状态 
				}else if(能向下移动){
					下个状态添加进状态
				}else if(能向左移动){
					下个状态添加进状态
				}else if(能向右移动){
					将下一个状态添加进状态栏
				}
			}
		}
}
**************************************************/



/***************** 寻路算法实现 *******************/


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
               int *pCrashElement,
               int nCrashElementNum
               )
{
  
  // 判断传入坐标是否正确
  while(true)
  {
    // 将坐标数据合法化
    dstPos.amend();
    // 检查目标坐标是否是是一个能够到达的点
    if(ThisPointIsCarsh((pMap[ dstPos[ emPostion::posRow ] ][ dstPos[ emPostion::posCol ] ]) ,
                        pCrashElement,
                        nCrashElementNum
                       )
       )
    {
      /*************** 两种处理方法，可根据需求调整 ***************/
      // 如果是墙就将坐标向其下方移动一个后再判断，
      // 因为在吃豆人地图的每一列中至少会有一个位置不是墙壁
      dstPos = dstPos.getActionPostion(emAction::actDown);
      // 另一种处理方法，返回 -1
      // return -1;
    }
    else
    {
      break;
    }
  }

  // 地图数组，用于保存走过的路
  int nPassPostion[ MAPROW ][ MAPCOL ] = { 0 };

  // 寻路状态结点结构体，这里不放CPostion类型了，影响效率
  typedef struct FindState
  {
    CPostion Pos;
    enum emAction myAction;
    enum emAction firstAction;
  } FindState;

  // 两个状态结点数组，用于保存寻址信息
  FindState* nowStateArr = new FindState[ 300 ];
  FindState* preStateArr = new FindState[ 300 ];
  FindState* pTempArr;
  // 两个数组下标
  int nNowArrCur = -1;
  int nPreArrCur = -1;

  // 临时坐标
  int nTempRow = 0;
  int nTempCol = 0;

  // 初始数组信息
  ++nPreArrCur;
  preStateArr[ nPreArrCur ].Pos = srcPos;
  preStateArr[ nPreArrCur ].myAction = emAction::actUp;
  preStateArr[ nPreArrCur ].firstAction = emAction::actUp;
  nPassPostion[ srcPos[ emPostion::posRow ] ][ srcPos[ emPostion::posCol ] ] = 1;

  int nFindNum = 0;

  CPostion tempPos;
  CPostion savePos;
  int nNewRow = 0;
  int nNewCol = 0;
  int nRet = 0;
  while(true)
  {
    // 判断是否到达目标坐标点
    for(int i = 0; i <= nPreArrCur; ++i)
    {
      tempPos = preStateArr[ i ].Pos;
      if(tempPos == dstPos)
      {
        nRet = preStateArr[ i ].firstAction;
        delete[] nowStateArr;
        delete[] preStateArr;
        return nRet;
      }
    }

    ++nFindNum;
    // 从当前状态继续寻找
    for(int i = 0; i <= nPreArrCur && nPreArrCur >= 0; ++i)
    {
      // 获取状态坐标值
      savePos = preStateArr[ i ].Pos;
      
      // 遍历四个方向
      for(int j = emAction::actUp; j <= emAction::actRight; ++j)
      {
        // 获取状态坐标值
        tempPos = savePos;
        // 判断改坐标是否可通过
        nTempRow = tempPos.getActionPostion(j)[ emPostion::posRow ];
        nTempCol = tempPos.getActionPostion(j)[ emPostion::posCol ];
        if(ThisPointIsCarsh((pMap[ nTempRow ][ nTempCol ]) ,
                            pCrashElement,
                            nCrashElementNum
                           )
          )
        {
          // 不能朝该方向移动
          continue;
        }

        // 可以移动，更新坐标信息
        tempPos = tempPos.getActionPostion(j);
        // 获取移动后的新坐标
        nNewRow = tempPos[ emPostion::posRow ];
        nNewCol = tempPos[ emPostion::posCol ];

        // 非首次
        if(nFindNum > 1 && nPassPostion[ nNewRow ][ nNewCol ] == 0)
        {
          ++nNowArrCur;
          nowStateArr[ nNowArrCur ].Pos = tempPos;
          nowStateArr[ nNowArrCur ].myAction = (emAction)j;
          // 关键在这一步，保存前一状态中记录的初始方向
          nowStateArr[ nNowArrCur ].firstAction = preStateArr[i].firstAction;
          nPassPostion[ nNewRow ][ nNewCol ] = nFindNum;

        }
        // 首次
        else if(nFindNum == 1 && nPassPostion[ nNewRow ][ nNewCol ] == 0)
        {
          ++nNowArrCur;
          nowStateArr[ nNowArrCur ].Pos = tempPos;
          nowStateArr[ nNowArrCur ].myAction = (emAction)j;
          nowStateArr[ nNowArrCur ].firstAction = (emAction)j;
          nPassPostion[ nNewRow ][ nNewCol ] = nFindNum;
        }
      }
    }

    // 交换寻址状态数组指针所指空间，从而保存当前状态，丢弃之前的状态
    pTempArr = preStateArr;
    preStateArr = nowStateArr;
    nowStateArr = pTempArr;
    // 重置数组下标
    nPreArrCur = nNowArrCur;
    nNowArrCur = -1;
  }
}




/******************** 坐标类实现 **********************/

CPostion::CPostion()
  : m_nRow(0) , m_nCol(0)
{
}

CPostion::CPostion(int nRow , int nCol)
  : m_nRow(nRow) , m_nCol(nCol)
{

}

CPostion::CPostion(CPostion& obj)
{
  m_nRow = obj.m_nRow;
  m_nCol = obj.m_nCol;
}

CPostion::~CPostion()
{
}

// 获取对应横纵坐标
int& CPostion::operator[](int nIndex)
{
  return (nIndex == emPostion::posRow) ? m_nRow : m_nCol;
}


// 坐标赋值
CPostion& CPostion::operator=(CPostion& obj)
{
  m_nRow = obj.m_nRow;
  m_nCol = obj.m_nCol;
  return *this;
}


// 判断坐标是否相等
int CPostion::operator==(CPostion& obj)
{
  if(m_nRow == obj.m_nRow)
  {
    if(m_nCol == obj.m_nCol)
    {
      return 1;
    }
  }
  return 0;
}
int CPostion::operator!=(CPostion& obj)
{
  return !(*this == obj);
}

// 将两个坐标相加（直接相加）
CPostion CPostion::operator+(CPostion& obj)
{
  CPostion tempPos = *this;
  tempPos.m_nRow += obj.m_nRow;
  tempPos.m_nCol += obj.m_nCol;
  tempPos.amend();
  return tempPos;
}

// 获取两个坐标差（横竖差坐标的差，可以是负值）
CPostion CPostion::operator-(CPostion& obj)
{
  CPostion tempPos = *this;
  tempPos.m_nRow -= obj.m_nRow;
  tempPos.m_nCol -= obj.m_nCol;
  return tempPos;
}

// 将坐标与数字相乘
CPostion CPostion::operator*(int nNum)
{
  CPostion tempPos = *this;
  tempPos.m_nRow *= nNum;
  tempPos.m_nCol *= nNum;
  return tempPos;
}

// 修正坐标（防止越界）
void CPostion::amend()
{
  m_nRow = (m_nRow + MAPROW) % MAPROW;
  m_nCol = (m_nCol + MAPCOL) % MAPCOL;
}

// 设置坐标
void CPostion::set(int nRow , int nCol)
{
  m_nRow = nRow;
  m_nCol = nCol;

  amend();
}


// 获取这个方向下个坐标
CPostion CPostion::getActionPostion(int nAction)
{
  CPostion nextPos = *this;
  // 更改元素Row位置
  nextPos[ emPostion::posRow ] += ((2 & nAction) != 0) ? 0 :
    (((1 & nAction) == 0) ? -1 : 1);

  // 更改元素Col位置
  nextPos[ emPostion::posCol ] += ((2 & nAction) == 0) ? 0 :
    (((1 & nAction) == 0) ? -1 : 1);

  nextPos[ emPostion::posRow ] += (nextPos[ emPostion::posRow ] < 0) ? MAPROW : 0;
  nextPos[ emPostion::posCol ] += (nextPos[ emPostion::posCol ] < 0) ? MAPCOL : 0;

  nextPos.amend();

  return nextPos;
}

// 根据方向修改坐标
void CPostion::changePostion(int nAction)
{
  *this = getActionPostion(nAction);
}


/*
* 简单的碰撞检测
* nMapElement:      地图上的元素
* pCarshElement:    会发生碰撞元素的数组
* nCarshElementNum: 数组元素个数
*
* 注：在吃豆人游戏模式中对于鬼而言，
      只有墙是不可穿越的，
      但为了算法的可扩展性采用了数组的形式，
      从而实现地图中增加新的鬼不可穿越元素
      算法无需修改的目的。
      其实也可以采用位运算的方式，
      但这样对地图元素定义有要求，
      所以不采用。
*/
bool ThisPointIsCarsh(int nMapElement ,
                      int* pCarshElement ,
                      int nCarshElementNum)
{
  for(int i = 0; i < nCarshElementNum; ++i)
  {
    if(nMapElement == *(pCarshElement + i))
    {
      return true;
    }
  }

  return false;
}
