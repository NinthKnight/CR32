#ifndef CTCPSOCKET_H
#define CTCPSOCKET_H

#include <ws2tcpip.h>
#include <WinSock2.h>
#include <windows.h>
#include <string>
#include <map>

//代表客户端的信息（会话）
struct CClientSession{
    CClientSession(SOCKET s, sockaddr_in addr){
        m_s = s;
        m_addr = addr;
    }

    SOCKET m_s;
    sockaddr_in m_addr;
};

class CTcpSocket
{
public:
    CTcpSocket();
    ~CTcpSocket();

    bool StartUp();

    bool CreateAndBind(int nPort);

    bool Accept();

    int Send(SOCKET s, char* pData, int nLength);

    int Recv(SOCKET s, char* pData, int nLength);

    bool Close(SOCKET s);


    SOCKET m_AcceptSocket;
    std::map<SOCKET, CClientSession*> m_ClientMap;

};

#endif // CTCPSOCKET_H
