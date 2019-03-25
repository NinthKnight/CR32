// TestSocket.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <ws2tcpip.h>
#include <WinSock2.h>
#include <windows.h>
#include <thread>
#include "../../common/common.h"

#pragma comment(lib, "ws2_32.lib")

//��ȡָ�����ȵ�����
bool RecvData(SOCKET s, char* pBuf, int nData) {

    int nTotalSize = 0;
    while (nTotalSize < nData) {
        int nRet = recv(s,
            pBuf + nTotalSize,
            nData - nTotalSize,
            0);
        if (nRet > 0) {
            nTotalSize += nRet;
        }
        else {
            return false;
        }
    }

    return true;
}


int main()
{
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;

    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        /* Tell the user that we could not find a usable */
        /* WinSock DLL.                                  */
        return 0;
    }

    SOCKET sClient = socket(AF_INET,
        SOCK_STREAM,
        IPPROTO_TCP);

    //bind ��

    sockaddr_in addr = { 0 };
    InetPton(AF_INET,
        _T("127.0.0.1"),
        &addr.sin_addr.S_un.S_addr);//INADDR_ANY;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(8888);
    DWORD dwIP;

    int nRet = connect(sClient, (sockaddr*)&addr, sizeof(sockaddr));
    if (nRet == SOCKET_ERROR) {
        //WSAGetLastError();
        return 0;
    }
    
    char szBuf[1024] = { 0 };
    bool bRet = false;
    std::thread recvThread([&](SOCKET sClient) {
        //ѭ����ȡ����
        while (true) {
            
            //int nHead = sizeof(tagPacket);
            tagPacket* pkt = (tagPacket*)szBuf;
            //�ȶ���ͷ
            bRet = RecvData(sClient,
                                      (char*)pkt,
                                      sizeof(tagPacket));
            
            //�������ʾ�Ѿ��ɹ��Ķ�ȡ�˰�ͷ����
            bRet = RecvData(sClient, (char*)pkt->szData, pkt->nSize);

            switch (pkt->btCmd)
            {
                //����������
                case CLIENT_PUBLIC: {
                    printf(pkt->szData);
                }
                break;

                default:
                    break;
            }
            //closesocket(sClient);

        }

    }, sClient);
    
    char szData[1024] = { 0 };
    //��ȡ�û������룬����������
    while (true) {
        //���
        tagPacket* pkt = (tagPacket*)szData;
        fgets(pkt->szData, 256, stdin);

        //��������
        int nLen = strlen(pkt->szData) + 1;
        pkt->btCmd = CLIENT_PUBLIC;
        pkt->nSize = nLen;


        send(sClient, (char*)pkt, sizeof(tagPacket) + nLen, 0);
    }
    
    return 0;
}

