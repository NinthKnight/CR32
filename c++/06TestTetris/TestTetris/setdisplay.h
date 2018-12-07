#pragma once
#include <windows.h>
#include <stdio.h>

/********����̨������Ʋ�ɫ����*********/

/*************************************
�����ɫ����̨��һ��С���⣺
    ������õĸ߶ȶ�һ�У����һ�У���
    ��һ�п���������ݣ�
    ����Ҫ������ݵ����һ�У�
    �������ᱻ������һ�У���һ�л���ʧ��
    ��ζ����������������������£�
    Ҫ�����һ��ȫ�ڣ�
    Ҫ�����½���һ��խ�ڿ飬
    ����&���Ӵ����е�8�����Կ���չʾ����
**************************************/


/*********** ��ȵĻ�����λ�������� ***********/
// ����Ϊ2��ζ��1��Ϊ2��Ӣ�Ŀ�Ȼ�1�����ֿ��      
#define WIDTH_UNIT 2  // �ɸ��������޸�



/*************************************
��ɫ����
**************************************/
#define COLOR_BLACK             0x00    // ��ɫ
#define COLOR_BLUE              0x01    // ��ɫ
#define COLOR_GREEN             0x02    // ��ɫ
#define COLOR_LIGHTBLUE         0x03    // ����ɫ
#define COLOR_RED               0x04    // ��ɫ
#define COLOR_PURPLE            0x05    // ��ɫ
#define COLOR_YELLOW            0x06    // ��ɫ
#define COLOR_WHITE             0x07    // ��ɫ
#define COLOR_GRAY              0x08    // ��ɫ
#define COLOR_THIN_BLUE         0x09    // ����ɫ
#define COLOR_THIN_GREEN        0x0A    // ����ɫ
#define COLOR_THIN_LIGHT_GREEN  0x0B    // ��ǳ��ɫ
#define COLOR_THIN_RED          0x0C    // ����ɫ
#define COLOR_THIN_PURPLE       0x0D    // ����ɫ
#define COLOR_THIN_YELLOW       0x0E    // ����ɫ
#define COLOR_LIGHT_WHITE       0x0F    // ����ɫ


/*******************************
���ܣ�����ǰ����ɫ

f ǰ��ɫ
b ����ɫ

ԭ��
  1�ֽ�����
  ��4�ֽ�Ϊǰ������4�ֽ�Ϊ����
********************************/
#define SetConsoleColor( f , b ) ( ( f ) + ( ( b ) << 0x04 ) )


/***********************************
���Ժ��� & ����
************************************/
void TestWindowSizeAndColor();


/*************************************
�������ܣ���ӡ�ַ�������̨�ƶ�λ��
nHigh: �߶�X�У�����
nWide: ���Y�У�����
pszChar: ��ӡ���ַ�����һ���ַ�ҲҪ���ַ�������ʽ��
wArr: ��ӡ�ַ������ԣ���ɫ
      ��ͨ��SetConsoleColor�����ñ���ɫ

ע��: ������ʾ�������Ϻ��һֱ����
      ��� 1 ��Ϊ 1 ������ �� ����Ӣ�ģ�
      ��ͨ�� ��Ⱥ� WIDTH_UNIT ������
**************************************/
void WriteChar(int nHigh , int nWide , char* pszChar , WORD wArr);


/*************************************
��������: ���ô�����Ϣ
*pszWindewTitle: ��������
nHigh: �߶�X�У�����
nWide: ���Y�У�����
�ɹ�����ֵ: TRUE

ע�⣺��ֵ����̫�����������Ǹ߶�
      ��� 1 ��Ϊ 1 ������ �� ����Ӣ�ģ�
      ��ͨ�� ��Ⱥ� WIDTH_UNIT ������
*************************************/
BOOL SetWindowSize(char *pszWindowTitle , int nHigth, int nWide);

