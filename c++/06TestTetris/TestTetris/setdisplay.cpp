#include "stdafx.h"
#include "setdisplay.h"


/*********************************
���Ժ��� & ����
**********************************/
void TestWindowSizeAndColor()
{
  // 1. ���ÿ���̨����ʹ��ڴ�С
  SetWindowSize("����̨��ɫ��������" , // ����
                30, // �߶� 30 �� // ��1920*1080����ʾ�������ֵΪ60
                30  // ��� 30 �� // 1 �� = 1 ������ �� 2 ��Ӣ�� 
                );

  // 2. �ڵ�һ�����һ�δ�����������
  WriteChar(0 ,  // �� 1 ��
            0 ,  // �� 1 ��
            "����һ�δ�����������0123456789ABCDEF" ,
            SetConsoleColor( COLOR_BLACK , // ��ɫǰ��
                             COLOR_WHITE)  // ��ɫ����
            );


  // 3. �ڵ��������һ�е�ǳ��ɫ
  char szBuff[ MAXBYTE ] = { 0 };
  // ����һ������Ϊ60���ո���ַ���
  sprintf_s(szBuff , MAXBYTE , "%60c" , ' ');
  WriteChar(2 ,  // �� 3 ��
            0 ,  // �� 1 ��
            szBuff ,   // 60���ո�
            SetConsoleColor( COLOR_BLACK , // ��ɫǰ��
                             COLOR_THIN_LIGHT_GREEN )  // ��ǳ��ɫ
            );
            

  // 4. �ڵ��������һ��ǳ��ɫ��������
  WriteChar(4 ,  // �� 5 ��
            0 ,  // �� 1 ��
            "����һ�λ��еİ�����\n0123456789ABCDEF<--��Щ���ֱ�������˵����У�����֧���Զ����У���������ݻ��Զ�����һ��" ,
            COLOR_THIN_GREEN
            );


  // 5. ����Ļ�м��ӡ16����ɫ
  // ��Ҫ����ͨ�����ո����ñ���ɫ
  for(int i = 0; i < 0x04; ++i)
  {
    for(int j = 0; j < 0x04; ++j)
    {
      WriteChar(i + 12 , // �ӵ�13�п�ʼ
                j + 12 , // �ӵ�13�п�ʼ
                "  " , // �����ո�
                SetConsoleColor( COLOR_BLACK , // ��ɫǰ�� 
                                 (WORD)(i * 4 + j) )    // ����ɫ
                );
    }
  }


  // 6. �ڵ������������һ�δ������ķ���
  WriteChar(27 ,  // �� 28 ��
            0 ,   // �� 1 ��
            "���ţ��������������������������������������ܣޣߣ�  " ,
            SetConsoleColor( COLOR_THIN_BLUE ,   // ǳ��ǰ��
                             COLOR_LIGHT_WHITE)  // ����ɫ����
            );


  // 7. �����һ�����һ������ɫ
  WriteChar(29 ,  // �� 30 ��
            0 ,  // �� 1 ��
            szBuff,
            SetConsoleColor( COLOR_BLACK , // ��ɫǰ��
                             COLOR_LIGHT_WHITE )  // ����ɫ����
            );


  // 8. ����չ��
  // ���������һ���������
  WriteChar(30 ,  // �� 31 ��
            0 ,   // �� 1 ��
            "�޷������Bug����:����30��,�����ǵ�31��,�ٶ�Ӹ��ո������� " ,
            SetConsoleColor( COLOR_THIN_BLUE ,   // ǳ��ǰ��
                             COLOR_LIGHT_WHITE)  // ����ɫ����
            );
}


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
*************************************/
void WriteChar(int nHigh , int nWide , char* pszChar , WORD wArr)
{
	CONSOLE_CURSOR_INFO cii;
	cii.dwSize = 1;
	cii.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE) , &cii);
	COORD loc;
	loc.X = nWide * (WIDTH_UNIT);
	loc.Y = nHigh;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , wArr);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE) , loc);
	printf(pszChar);
}


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
BOOL SetWindowSize(char *pszWindowTitle , int nHight, int nWide)
{
	// Title
  nWide *= (WIDTH_UNIT);
  // nHight -= 1;
  nWide -= 1;
	SetConsoleTitleA(pszWindowTitle);
	HANDLE hStdin , hStdOut;
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	// get max console window size
	COORD pos = GetLargestConsoleWindowSize(hStdOut);
	COORD BufferSize = { pos.X , pos.Y };
	// set console buffer size
	if(!SetConsoleScreenBufferSize(hStdOut , BufferSize)){
		// set console buffer size FALSE
		printf("buffer err(%d,%d)%d\n" , BufferSize.X , BufferSize.Y , GetLastError());
		return FALSE;
	}
	SMALL_RECT srctWindow = { 0 , 0 , nWide , nHight };
	if(!SetConsoleWindowInfo(hStdOut , TRUE , &srctWindow)){
		// set console window size FALSE
		printf("size err %d\n" , GetLastError());
		return FALSE;
	}
	COORD Buffer = { nWide + 1 , nHight + 1 };
	// set console buffer size
	if(!SetConsoleScreenBufferSize(hStdOut , Buffer)){
		// set console buffer size FALSE
		printf("buffer err(%d, %d)%d\n" , BufferSize.X , BufferSize.Y , GetLastError());
		return FALSE;
	}
	return TRUE;
}
