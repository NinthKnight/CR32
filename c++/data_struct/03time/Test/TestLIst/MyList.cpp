#include "stdafx.h"
#include "MyList.h"


CMyList::CMyList(){
    m_pHead = new CMyNode(0);
    m_nSize = 0;
}


CMyList::~CMyList()
{
}

//¡°ÉÚ±ø¡±

//llvm, ollvm
void CMyList::push_back(const T_LIST int & n){

    CMyNode* p = new CMyNode(n);

    CMyNode* tmp = m_pHead;
    while (tmp->m_pNext != nullptr) {
        tmp = tmp->m_pNext;
    }

    tmp->m_pNext = p;
    p->m_pPre = tmp;

    m_nSize++;
    return;
}

//    head    1    2    3
//    head    0    1    2    3

void CMyList::push_front(const T_LIST int & n){

    CMyNode* pNew = new CMyNode(n);
    CMyNode* pNext = m_pHead->m_pNext;

    m_pHead->m_pNext = pNew;
    
    pNew->m_pPre = m_pHead;
    pNew->m_pNext = pNext;

    if (pNext != nullptr) {
        pNext->m_pPre = pNew;
    }

    m_nSize++;
}
