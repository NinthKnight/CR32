// TestSocket.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <ws2tcpip.h>
#include <WinSock2.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

//�����                         �ͻ���
// 1. socket                    1. socket
// 2. bind                      2. bind(optional)
// 3. listen                    3. connect
// 4. accept
// 5. recv/send                 4. recv/send
// 6. closesocket               5. closesocket

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
    addr.sin_port = htons(1234);
    DWORD dwIP;

    int nRet = connect(sClient, (sockaddr*)&addr, sizeof(sockaddr));
    if (nRet == SOCKET_ERROR) {
        //WSAGetLastError();
        return 0;
    }

    char szBuf[256] = { 0 };

    send(sClient, "Hello", 6, 0);


    //closesocket(sClient);
    int nReadedSize = recv(sClient, szBuf, 256, 0);
    if (nReadedSize > 0) {
    
        //��ʾ�ɹ��յ���nReadedSize������
        OutputDebugStringA("�ɹ��յ���nReadedSize������");
    }
    else if (nReadedSize == 0) {
        //��ʾtcp���Źر�
        OutputDebugStringA("���Źر�");

        //int nSendedSize = send(sClient, "Hello World!", strlen("Hello World!") + 1, 0);

        shutdown(sClient, SD_SEND);
    }
    else {
        //��ʾ������
        OutputDebugStringA("SOCKET_ERROR");
    }

    closesocket(sClient);


    return 0;
}

