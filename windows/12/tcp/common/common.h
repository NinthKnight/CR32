#pragma once
#include <windows.h>
//packet:
// 1. ���ͱ�ʶ
// 2. ���ݳ���
// 3. ����

enum {
    // client --> server
    CLIENT_PUBLIC = 1,


    //server->client
    SERVER_PUBLIC_REPLY
};

#pragma pack(push, 1)
struct tagPacket {
    BYTE btCmd;
    size_t nSize;
    char szData[];
};
#pragma pack(pop)