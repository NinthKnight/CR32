// Server.cpp : �������̨Ӧ�ó������ڵ㡣
//



#include "stdafx.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <Winsock2.h>
#include <thread>

#define CLIENT
#include "../../common/macro.h"


#pragma comment(lib, "ws2_32.lib")


void OnServerScreenData(SOCKET s, char* pData, int nLength);

//SOCKET���׽��֣���� �� ��ʼ��
//UDP�������ӵ�
//TCP�������ӵ�
SOCKET sClient;
HANDLE hMyCmdWrite;

//�������߳�
void HeartBeat()
{
	bool bRet = false;
	while (true) {
		Sleep(20 * 1000);
		bRet = SendData(sClient, CLIENT_HEART, NULL, 0);
		if (!bRet) {
			break;
		}
	}

}


void Init()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(2, 2);

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		/* Tell the user that we could not find a usable */
		/* WinSock DLL.                                  */
		return;
	}

	//1 ����SOCKET���׽��֣�
	int nRet;
	//TCP
	sClient = socket(AF_INET,
		SOCK_STREAM,//������, ��ʽ
		IPPROTO_TCP);

	//�󶨶˿�1-65535�� IP 0.0.0.0
	sockaddr_in name;
	name.sin_family = AF_INET;
	name.sin_port = htons(1234);
	name.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	int nLength = sizeof(sockaddr_in);

	//4 accept ��������
	char szBuf[256] = { 0 };
	char szBufFmt[256] = { 0 };
	
	nRet = connect(sClient, (sockaddr*)&name, nLength);

	//
	if (nRet == SOCKET_ERROR) {
		return;
	}

  OnServerScreenData(sClient, NULL, 0);

	//std::thread* ptd = new std::thread(HeartBeat);
}

void OnServerScreen(SOCKET s, char* pData, int nLength) {
	//����������߷������յ����ݿ��Դ���screen
	tagPacket pkt;
	pkt.code = CLIENT_SCREEN_REPLY;
	pkt.length = 0;
	send(sClient,
		(char*)&pkt,
		sizeof(tagPacket),
		0);
	
}

void OnServerScreenData(SOCKET s, char* pData, int nLength) {

	//��ȡ��Ļ�����ݣ���ת��bmp��ʽ
	HWND hDesktop =  GetDesktopWindow();
	RECT rc = {0};
	HDC hDesktopDC = NULL;
	HDC hMemDC = NULL;
	BOOL bRet = FALSE;
	HBITMAP  hBitmap = NULL;
	int nWidth = 0;
	int nHeight = 0;
	int nSize = 0;
	char* pBuf = NULL;

	if (hDesktop == NULL) {
		goto SAFE_EXIT;
	}

	hDesktopDC = GetDC(hDesktop);
	if (hDesktopDC == NULL) {
		goto SAFE_EXIT;
	}

	hMemDC = CreateCompatibleDC(hDesktopDC);
	if (hMemDC == NULL) {
		goto SAFE_EXIT;
	}

	//��ȡ��͸�
	bRet = GetWindowRect(hDesktop, &rc);
	if (!bRet) {
		goto SAFE_EXIT;
	}

	nWidth = rc.right - rc.left;
	nHeight = rc.bottom - rc.top;

	hBitmap = CreateCompatibleBitmap(hDesktopDC, nWidth, nHeight);
	if (hBitmap == NULL) {
		goto SAFE_EXIT;
	}
	SelectObject(hMemDC, hBitmap);

	bRet = BitBlt(hMemDC, 0, 0, nWidth, nHeight, hDesktopDC, 0, 0, SRCCOPY);
	if (!bRet) {
		goto SAFE_EXIT;
	}

	//��ȡ���ݣ��������
	nSize = 4 * nWidth * nHeight;
    pBuf = new char[nSize + 8];
	if (pBuf == NULL) {
		goto SAFE_EXIT;
	}

	*(int*)pBuf = nWidth;
	*((int*)pBuf + 1) = nHeight;

	GetBitmapBits(hBitmap, nSize, pBuf + 8);

	SendData(s, CLIENT_SCREEN_DATA, pBuf, nSize + 8);

SAFE_EXIT:
	if (pBuf != NULL) {
		delete[] pBuf;
	}

	if (hBitmap != NULL) {
		DeleteObject(hBitmap);
	}

	if (hMemDC != NULL) {
		DeleteDC(hMemDC);
	}

	if (hDesktopDC != NULL) {
		ReleaseDC(hDesktop, hDesktopDC);
	}



}

void HandleData() {
	
	tagPacket pkt;
	char* pData = NULL;

	while (true) {
		//��ȡ��ͷ
		bool bRet = RecvData(sClient,
			(char*)&pkt,
			sizeof(tagPacket));
		if (!bRet)
		{
			return;
		}

		if (pkt.length > 0) {
			//��ȡ���ĸ�������
		    pData = new char[pkt.length];
			bool bRet = RecvData(sClient,
				(char*)pData,
				pkt.length);
			if (!bRet)
			{
				return;
			}
		}
	
		//��ʾ�Ѿ��ɹ����յ���һ�����������ʼ���������
		switch (pkt.code)
		{
			case SERVER_SCREEN:
			{
				OnServerScreen(sClient, pData, pkt.length);
			}
			break;

			case SERVER_SCREEN_DATA:
			{
				OnServerScreenData(sClient, pData, pkt.length);
			}
			break;

		default:
			break;
		}


		if (pData != NULL) {
			delete[] pData;
			pData = NULL;
		}
	}
}



int Mycmd() {

	std::thread t(HandleData);

	t.join();

	return 0;
}

int main()
{
	Init();

	Mycmd();

	return 0;
}

