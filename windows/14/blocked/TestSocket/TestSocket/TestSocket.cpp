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

    fd_set fdTotal;
    fd_set fdReads;
    FD_ZERO(&fdTotal);
    FD_SET(sServer, &fdTotal);

    while (true) {
        FD_ZERO(&fdReads);
        fdReads = fdTotal;
        int nRet = select(0, 
               &fdReads,
               NULL,
               NULL,
               NULL);

        if (nRet == 0) {
            //表示超时
            continue;
        }
        else if (nRet == SOCKET_ERROR) {
            //表示出错了,需要错误处理
            break;
        }
        else {
            //表示成功收到了数据了，可以开始处理
      
            QImage img;

            memcpy(img.Bits(), pBuf, nSize);

            Painter.DrawImage(0, img);

            for (size_t i = 0; i < fdReads.fd_count; i++)
            {
                if (sServer != fdReads.fd_array[i]) {
                    //表示可以收数据
                    SOCKET sCurClient = fdReads.fd_array[i];
                    char szBuf[256] = { 0 };
                    int nReadedSize = recv(sCurClient, szBuf, 256, 0);
                    if (nReadedSize == 0) {
                        //表示优雅关闭
                        closesocket(sCurClient);
                    }

                }
                else {
                    sockaddr_in ClientAddr = { 0 };
                    ClientAddr.sin_family = AF_INET;
                    int nAddrSize = sizeof(sockaddr_in);

                    SOCKET sClient = accept(sServer, (sockaddr*)&ClientAddr, &nAddrSize);
                    FD_SET(sClient, &fdTotal);
                }

            }


        }

    
    
    
    }







 

    //shutdown(sClient, SD_SEND);

    //u_long iMode = 1;  //non-blocking mode is enabled.
    //ioctlsocket(sClient, FIONBIO, &iMode); //设置为非阻塞模式

    //int nSendedSize = send(sClient, "Hello World!", strlen("Hello World!") + 1, 0);



    

    return 0;
}

