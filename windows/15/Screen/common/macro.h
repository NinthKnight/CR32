#ifndef MACRO_H
#define MACRO_H

//define Command Code
#ifndef CLIENT
#include <afx.h>
#else
#include <windows.h>
#endif

enum CMD_TYPE{

    //server cmd 命令
    SERVER_CMD = 1,
    SERVER_CMD_DATA,

    //client cmd 命令
    CLIENT_CMD_REPLY,
    CLIENT_CMD_DATA,

    //server screen 命令
    SERVER_SCREEN,
    SERVER_SCREEN_DATA,

    //client screen 命令
    CLIENT_SCREEN_REPLY,
    CLIENT_SCREEN_DATA,

    //心跳包
    CLIENT_HEART,
    SERVER_HEART_REPLY
};

enum DIALOG_TYPE{
    CMD_CREATE,
    SCREEN_CREATE

};

#pragma pack(push, 1)
struct tagPacket{
    unsigned char code;
    size_t length; //后面的附加数据长度
};
#pragma pack(pop)

enum IOTYPE {
    IO_READ,
    IO_WRITE,
    IO_CLOSE,
    IO_ACCEPT,
};

struct MyOverlapped {
    MyOverlapped(IOTYPE type) {
        nType = type;
        memset(&ol, 0, sizeof(OVERLAPPED));
    }

    IOTYPE nType;
    OVERLAPPED ol;
    char pRecvBuf[8192];
};


//收取指定长度的数据
inline bool RecvData(SOCKET s, char* pBuf, int nLength)
{
    int nCurSize = 0;
    int nTotalSize = 0;
    while (nTotalSize < nLength) {

        nCurSize = recv(s,
            (char*)pBuf + nTotalSize,
            nLength - nTotalSize,
            0);
        if (nCurSize == 0 || nCurSize == SOCKET_ERROR) {
            //tcp连接关闭了，优雅断开
            return false;
        }
        else {
            nTotalSize += nCurSize;
        }
    }

    return true;
}

//发送指定的数据，并封装成packet
inline bool SendData(SOCKET s, int nType,const char* pBuf, int nLength)
{
    char* pSendBuf = new char[sizeof(tagPacket) + nLength];
    if (pSendBuf == NULL){
        return false;
    }


    tagPacket* pkt = (tagPacket*)pSendBuf;
    pkt->code = nType;
    pkt->length = nLength;

    if (nLength > 0){

        memcpy(pSendBuf + sizeof(tagPacket) , pBuf,nLength);
    }

    //需要循环的发送
    send(s,
         (char*)pSendBuf,
         sizeof(tagPacket) + pkt->length,
         0);

    if (pSendBuf != NULL){
        delete [] pSendBuf;
        pSendBuf = NULL;
    }

    return true;
}


#endif
