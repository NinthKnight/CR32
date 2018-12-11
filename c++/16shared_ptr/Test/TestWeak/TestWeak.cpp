// TestWeak.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <memory>
//循环引用的问题

class CSon;
class CFather {
public:
    CFather() {
        //m_pSon = nullptr;
    }

    void Set(std::shared_ptr<CSon> pSon) {
        m_pSon = pSon;
    }

    ~CFather() {
        //if (m_pSon != nullptr) {
        //    delete m_pSon; 
        //}
        printf("~CFather()\r\n");
    }

private:
    std::weak_ptr<CSon> m_pSon;
};

class CSon {
public:
    CSon() {
        m_pFather = nullptr;
    }

    ~CSon() {
        printf("~CSon()\r\n");
    }

    void Set(std::shared_ptr<CFather> pFather) {
        m_pFather = pFather;
    }

private:
    std::shared_ptr<CFather> m_pFather;
};




int main()
{
    CFather* pFather = new CFather;
    CSon* pSon = new CSon;

    std::shared_ptr<CFather> father(pFather);
    std::shared_ptr<CSon> son(pSon);

    father->Set(son);
    son->Set(father);

    return 0;
}

