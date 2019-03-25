#pragma once
#include <windows.h>
//packet:
// 1. 类型标识
// 2. 数据长度
// 3. 数据

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