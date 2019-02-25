#include "stdafx.h"
#include "MyThreadPlool.h"
#include "SkyChaserHttp.h"

MyThreadPlool::MyThreadPlool()
{
}


MyThreadPlool::~MyThreadPlool()
{
}


DWORD ThreadFunc(LPVOID lpParam) {

    MyThreadPlool* pThis = (MyThreadPlool*)lpParam;
    CSkyChaserHttp http;
    string strRet;

    while (WaitForSingleObject(pThis->m_hSem, INFINITE) == WAIT_OBJECT_0)
    {


        //int nThreadID = GetCurrentThreadId();
        //取任务，并执行
        std::string str = pThis->getTask();

        //锁住该作用域
        pThis->m_mutex.lock();

        CURLcode code = http.sc_get(str.c_str(), strRet);
        if (code != CURLE_OK)
        {
            return 0;
        }

        if (200 == http.sc_getResponseCode())
        {
            printf("%s\r\n", str.c_str());
        }

        //printf("%d\r\n", pThis->m_TaskQue.size());

        pThis->m_mutex.unlock();
        //if (!str.empty())
        //{
        //    std::stringstream sStr;
        //    sStr << nThreadID << ": " << str.c_str();
        //    OutputDebugStringA(sStr.str().c_str());
        //}
    }
    return 0;
}


bool MyThreadPlool::Create()
{
    //创建一个信号灯/信号量
    m_hSem = CreateSemaphore(nullptr,
        0,
        0x7FFFFFFF,
        nullptr);

    //创建4个线程
    for (int i = 0; i < 4; i++)
    {
        m_hThreadAry[i] = CreateThread(nullptr,
                                       0,
                                       (LPTHREAD_START_ROUTINE)ThreadFunc,
                                       this,
                                       0,
                                       nullptr);
    }

    return true;
}

bool MyThreadPlool::Destroy()
{
    //CloseHandle(m_hSem);

    WaitForMultipleObjects(4, m_hThreadAry, TRUE, INFINITE);

    return true;
}

void MyThreadPlool::addTask(std::string str)
{
    //锁住该作用域
    std::lock_guard<std::mutex> guard(m_mutex);

    //加任务进队列
    m_TaskQue.push(str);

    //来任务了 信号量 + 1
    ReleaseSemaphore(m_hSem, 1, nullptr);
}

std::string MyThreadPlool::getTask()
{
    //锁住该作用域
    std::lock_guard<std::mutex> guard(m_mutex);

    //如果没有文本,返回空字符串
    if (m_TaskQue.size() == 0)
    {
        return "";
    }
    
    std::string str = m_TaskQue.front();
    m_TaskQue.pop();

    return str;
}
