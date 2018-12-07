#include <iostream>
/*
��Զ���˹������Ϸ���Է��������з�װ��ʵ�ְ������ǲ�����
���µĹ��ܣ��ƶ�����ת����ʾ�������·���
��ָ�����ͻ�����������ַ�����
*/

/*
  ��Ϸ��ͼ
*/
struct tagGameMap
{
  int nWidth;
  int nHeight;
  int *maps;
};

/*
  ������,����Ķ����ʾһ������
    һ�������������,����ͼ��Ҳ���Ƕ�ά��������,��ɫ
*/
class CTetrisBlock
{
private:
  //ö�ٳ���
  enum { BLOCKSIZE = 4 }; //�����С

  //ÿ���������ɫ
  int nColor;

public:
  //ÿһ�������ͼ��
  int block_map[BLOCKSIZE][BLOCKSIZE];

  //��ɫֵ
  enum eColor 
  { 
    RED, 
    GREEN, 
    BLUE 
  };

  //��ת�Ƕ�
  enum eRotateAngle
  {
    RO_LEFT, //������ת
    RO_RIGHT //������ת
  };

  //�ƶ�����
  enum eMoveDirection
  {
    MV_UP,
    MV_DOWN,
    MV_LEFT,
    MV_RIGHT
  };

 /*--------------------�ӿ�----------------------*/

  //�ƶ�
  bool move(tagGameMap *game_map, eMoveDirection eDirection, int nStep);

  //��ת
  bool rotate(eRotateAngle eAngle);

  //�˹���ֻ�ܴ�ӡblock_map��,��ʾ���ܲ��Ǵ˶�����ӵ��
  void display();

  //����һ��ָ��ͼ��ָ����ɫ�ķ���
  bool create(int block_map[BLOCKSIZE][BLOCKSIZE], int nColor);

  //����һ�����ͼ�������ɫ�ķ���
  bool create();
};

using namespace std;
int main()
{
  
  return 0;
}