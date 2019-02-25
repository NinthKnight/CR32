#include "stdafx.h"
#include "MyThreadPool.h"
#include <sstream>

CMyThreadPool::CMyThreadPool()
{
}


CMyThreadPool::~CMyThreadPool()
{
}

DWORD ThreadFunc(LPVOID lpParam) {

    CMyThreadPool* pThis = (CMyThreadPool*)lpParam;
    int nThreadID = GetCurrentThreadId();
    

    while (WaitForSingleObject(pThis->m_hSem, INFINITE) == WAIT_OBJECT_0) {
        //ȡ���񣬲�ִ��
        string str = pThis->getTask();

        if (!str.empty()) {
            stringstream sStr;
            sStr << nThreadID << ": " <<str.c_str();
            OutputDebugStringA(sStr.str().c_str());
        }
    }

    return 0;
}


bool CMyThreadPool::Create()
{
    //����һ���źŵ�/�ź���
    m_hSem = CreateSemaphore(NULL,
              0,
              0x7FFFFFFF,
              NULL);


    for (int i = 0; i < 4; i++) {
        m_hThreadAry[i] =  CreateThread(NULL,
            0,
            (LPTHREAD_START_ROUTINE)ThreadFunc,
            this,
            0,
            NULL);
    }

    return true;
}

bool CMyThreadPool::Destroy()
{
    //CloseHandle(m_hSem);
    
    WaitForMultipleObjects(4, m_hThreadAry, TRUE, INFINITE);

    return true;
}
