#pragma once

#include <Windows.h>
#include <queue>
#include <string>
#include <mutex>
#include <sstream>

class MyThreadPlool
{
public:
    MyThreadPlool();
    ~MyThreadPlool();

    //�������̳�
    bool Create();

    //���ٽ��̳�
    bool Destroy();

    //Ͷ������
    void addTask(std::string str);

    //ȡ����
    std::string getTask();

public:
    //�źŵ�
    HANDLE m_hSem;

    //������
    std::mutex m_mutex;

    //�������
    std::queue<std::string> m_TaskQue;
private:
    //�߳�
    HANDLE m_hThreadAry[4];

};

