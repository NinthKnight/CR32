#pragma once
#include <windows.h>
#include <queue>
#include <string>
#include <mutex>
using namespace std;

class CMyThreadPool
{
public:
    CMyThreadPool();
    ~CMyThreadPool();


    bool Create();

    bool Destroy();


    void addTask(string str) {
        m_mutex.lock();
        m_TaskQue.push(str);
        m_mutex.unlock();

        ReleaseSemaphore(m_hSem, 1, NULL);
    }

    string getTask() {


        lock_guard<mutex> guard(m_mutex);

        if (m_TaskQue.size() == 0) {
            return "";
        }
        string str = m_TaskQue.front();
        m_TaskQue.pop();

        return str;
    }

    HANDLE m_hThreadAry[4];

    queue<string> m_TaskQue;
    mutex m_mutex;

    HANDLE m_hSem;
};

