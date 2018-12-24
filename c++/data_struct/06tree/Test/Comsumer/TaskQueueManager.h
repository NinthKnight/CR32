#pragma once
#include <queue>
#include <memory>
#include "ITask.h"
#include <functional>

using fooType = std::function<void(void)>;

class TaskQueueManager
{
public:
    TaskQueueManager();
    ~TaskQueueManager();

    int size() {
        return m_TaskQue.size();
    }

    //添加任务
    void push(ITask* pTask) {
        //std::shared_ptr<ITask> sp(pTask);
        //m_TaskQue.push(sp);
    }

    void push(fooType f) {
        /m_TaskQue.push(f);
    }


    void Loop() {
    
        while (!m_TaskQue.empty()) {
        
            //std::shared_ptr<ITask> sp = m_TaskQue.front();
            //sp->Execute();
            //fooType f = m_TaskQue.front(); 
            //f();

            //m_TaskQue.pop();
        }
    
    }


private:
    //表示任务队列
    //std::queue<std::shared_ptr<ITask>> m_TaskQue;

    std::queue<fooType> m_TaskQue;
};

