#pragma once
class ITask
{
public:
    ITask();
    ~ITask();

    virtual void Execute() = 0;
};


class CAddTask : public ITask{
public:
    CAddTask(int n1, int n2) {
        m_nLeftOp = n1;
        m_nRightOp = n2;
    }

    virtual void Execute() {
    
        printf("%d + %d = %d\r\n", m_nLeftOp, m_nRightOp, m_nLeftOp + m_nRightOp);
    }

private:
    int m_nLeftOp;
    int m_nRightOp;
};

class CSubTask : public ITask {
public:
    CSubTask(int n1, int n2) {
        m_nLeftOp = n1;
        m_nRightOp = n2;
    }

    virtual void Execute() {

        printf("%d - %d = %d\r\n", m_nLeftOp, 
            m_nRightOp,
            m_nLeftOp - m_nRightOp);
    }

private:
    int m_nLeftOp;
    int m_nRightOp;
};