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

    SOCKET sClient = socket(AF_INET,
        SOCK_STREAM,
        IPPROTO_TCP);

    //bind 绑定

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
    
        //表示成功收到了nReadedSize的数据
        OutputDebugStringA("成功收到了nReadedSize的数据");
    }
    else if (nReadedSize == 0) {
        //表示tcp优雅关闭
        OutputDebugStringA("优雅关闭");

        //int nSendedSize = send(sClient, "Hello World!", strlen("Hello World!") + 1, 0);

        shutdown(sClient, SD_SEND);
    }
    else {
        //表示出错了
        OutputDebugStringA("SOCKET_ERROR");
    }

    closesocket(sClient);


    return 0;
}

