#include "stdafx.h"
#include "ctcpsocket.h"
#include <thread>
#include <sstream>
#include "../../common/common.h"

CTcpSocket::CTcpSocket()
{

}

CTcpSocket::~CTcpSocket()
{
    closesocket(m_AcceptSocket);
}

bool CTcpSocket::StartUp()
{
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;

    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        return false;
    }

    return true;
}

bool CTcpSocket::CreateAndBind(int nPort)
{
    int nRet = 0;
    m_AcceptSocket = socket(AF_INET,
                        SOCK_STREAM,//数据流, 流式
                        IPPROTO_TCP);

    if (m_AcceptSocket == SOCKET_ERROR){
        return false;
    }

    //绑定端口1-65535和 IP 0.0.0.0
    sockaddr_in name;
    name.sin_family = AF_INET;
    name.sin_port = htons(nPort);
    name.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

    //2 socket绑定ip和端口
    int namelen = sizeof(name);
    nRet = bind(m_AcceptSocket,
                    (struct sockaddr*)&name,
                    namelen);
    if (nRet == SOCKET_ERROR)
    {
        return false;
    }

    nRet = listen(m_AcceptSocket, SOMAXCONN);
    if (nRet == SOCKET_ERROR)
    {
        return false;
    }


    return true;
}

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


int RecvThread(CTcpSocket* pServer, CClientSession* pClient) {

    //处理当前session的数据收发
    SOCKET sClient = pClient->m_s;

    std::stringstream ss;
    ss << inet_ntoa(pClient->m_addr.sin_addr) << ":" << pClient->m_addr.sin_port << "online" << std::endl;

    //循环接收用户的数据
    char szBuf[1024] = { 0 };
    bool bRet = false;
    while (true) {
        
        //粘包 --->  封包
        tagPacket* pkt = (tagPacket*)szBuf;
        //先读包头
        bRet = RecvData(sClient,
            (char*)pkt,
            sizeof(tagPacket));

        //到这里表示已经成功的读取了包头数据
        bRet = RecvData(sClient, (char*)pkt->szData, pkt->nSize);

        switch (pkt->btCmd)
        {
            //处理公聊数据
        case CLIENT_PUBLIC: {
            for (auto client : pServer->m_ClientMap) {
                send(client.second->m_s, (char*)pkt, pkt->nSize + sizeof(tagPacket), 0);
            }
        }
        break;

        default:
            break;
        }


    }
    
    
    pServer->Send(sClient, (char*)ss.str().c_str(), ss.str().length() + 1);

    return 0;
}

bool CTcpSocket::Accept()
{
    sockaddr_in recvName = { 0 };
    recvName.sin_family = AF_INET;

    int nLength = sizeof(sockaddr_in);


    SOCKET sClient = accept(m_AcceptSocket, (sockaddr*)&recvName, &nLength);

    if (sClient == INVALID_SOCKET) {
        return false;
    }

    CClientSession* pClient =new CClientSession(sClient, recvName);

    //注意多线程操作是需要同步
    m_ClientMap.insert(std::pair<SOCKET, CClientSession*>(sClient, pClient));

    std::thread recvThread(RecvThread, this, pClient);
    recvThread.detach();

    return true;
}

int CTcpSocket::Send(SOCKET s, char *pData, int nLength)
{
    return send(s, pData, nLength, 0);
}

int CTcpSocket::Recv(SOCKET s, char *pData, int nLength)
{
    return recv(s, pData, nLength, 0);
}

bool CTcpSocket::Close(SOCKET s)
{
    closesocket(s);

    m_ClientMap.erase(s);

    return true;
}

