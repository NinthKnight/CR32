// TestSocket.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ctcpsocket.h"
#include <thread>
#pragma comment(lib, "ws2_32.lib")

CTcpSocket g_Server;

bool Start() {

    //初始化
    g_Server.StartUp();

    g_Server.CreateAndBind(1234);

    std::thread accptThread([&]() {
        //使用线程来等待客户端的连接
        while (true){
            g_Server.Accept();

        }

    });

    accptThread.join();
    
    return true;
}

int main()
{
    Start();
    
    return 0;
}

