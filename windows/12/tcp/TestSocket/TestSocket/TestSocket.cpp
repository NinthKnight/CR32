// TestSocket.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "ctcpsocket.h"
#include <thread>
#pragma comment(lib, "ws2_32.lib")

CTcpSocket g_Server;

bool Start() {

    //��ʼ��
    g_Server.StartUp();

    g_Server.CreateAndBind(1234);

    std::thread accptThread([&]() {
        //ʹ���߳����ȴ��ͻ��˵�����
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

