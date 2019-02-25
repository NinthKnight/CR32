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

    //创建进程池
    bool Create();

    //销毁进程池
    bool Destroy();

    //投递任务
    void addTask(std::string str);

    //取任务
    std::string getTask();

public:
    //信号灯
    HANDLE m_hSem;

    //互斥体
    std::mutex m_mutex;

    //任务队列
    std::queue<std::string> m_TaskQue;
private:
    //线程
    HANDLE m_hThreadAry[4];

};

