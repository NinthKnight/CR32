// TestSocket.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <ws2tcpip.h>
#include <WinSock2.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

//服务端                         客户端
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


    SOCKET sServer = socket(AF_INET,
        SOCK_STREAM,
        IPPROTO_TCP);

    //bind 绑定

    sockaddr_in addr = { 0 };

    DWORD dwIP;

    InetPton(AF_INET,
        _T("127.0.0.1"),
        &addr.sin_addr.S_un.S_addr);//INADDR_ANY;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234);

    int nRet = bind(sServer, (sockaddr*)&addr, sizeof(sockaddr));

    if (nRet == SOCKET_ERROR) {
        //WSAGetLastError();
        return 0;
    }

    nRet = listen(sServer, SOMAXCONN);
    if (nRet == SOCKET_ERROR) {
        //WSAGetLastError();
        return 0;
    }

    sockaddr_in ClientAddr = { 0 };
    ClientAddr.sin_family = AF_INET;
    int nAddrSize = sizeof(sockaddr_in);

    SOCKET sClient = accept(sServer, (sockaddr*)&ClientAddr, &nAddrSize);

    shutdown(sClient, SD_SEND);

    //int nSendedSize = send(sClient, "Hello World!", strlen("Hello World!") + 1, 0);
    char szBuf[256] = { 0 };
    int nReadedSize = recv(sClient, szBuf, 256, 0);
    if (nReadedSize == 0) {
        //表示优雅关闭
        closesocket(sClient);
    }


    

    return 0;
}

