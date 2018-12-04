#pragma once
#include "Imagebuf.h"
#include "Tank.h"

//用于显示
class CMyView
{
public:
    CMyView();
    ~CMyView();

    //绘制基本元素， nType = 1 表示砖  2 铁 3 浅蓝方块 4 深蓝方块 5 草 
    void DrawElement(int x, int y, int nType);

    //绘制爆炸效果 nType = 0-5 表示6种爆炸效果，效果逐渐递增
    void DrawBoom(int x, int y, int nType);

    //绘制坦克 nType = 0-3 表示4种坦克类型，nRotate表示旋转的方向
    void DrawTank(int x, int y, int nType, int nRotate);

    //绘制基地
    void DrawHomeBase(int x, int y);

    //绘制子弹 nType = 0 表示蓝色子弹 =1 表示红色子弹
    void DrawBullet(int x, int y, int nType);

    //绘制背景
    void DrawBg(int x, int y);

    //绘制地图
    void drawMap();

    //获取上下左右
    void OnUp();
    void OnDown();
    void OnLeft();
    void OnRight();

    //检查碰撞
    bool CheckImpact(int x, int y);

private:
    unsigned  char *MapPic[6];                //指向像素数据的指针  用以记录砖、铁……
    unsigned char *BoomPic[6];              //爆炸效果6张
    unsigned char *TankPic[4][4];           //坦克，上下左右 4张
    unsigned char* HomeBase;               //基地
    unsigned char * BulletPic[2];             //两种子弹
 

    CTank m_MyTank;//表示自己
    unsigned char m_mapData[26][26];
};

