#include "stdafx.h"
#include "MyList.h"


CMyList::CMyList(){
    m_pHead = new CMyNode(0);
    m_nSize = 0;
}


CMyList::~CMyList()
{
}

//“哨兵”

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

//    head    0    1    2    3
//    head    [0]    1    2    3
void CMyList::pop_front(){
    if (m_nSize == 0){
        return;
    }
   
    CMyNode* pFront = m_pHead->m_pNext;

    m_pHead->m_pNext = pFront->m_pNext;
    if (pFront->m_pNext != nullptr){
        pFront->m_pNext->m_pPre = m_pHead;
    }

    delete pFront;
    m_nSize--;
}

//    head    0    1    2    3
//    head    0    1    2    [3]
void CMyList::pop_back(){
    if (m_nSize == 0) {
        return;
    }

    CMyNode* pLast = m_pHead;
    while (pLast->m_pNext != nullptr) {
        pLast = pLast->m_pNext;
    }

    pLast->m_pPre->m_pNext = nullptr;

    delete pLast;
    m_nSize--;
}


//    head    0    1    3
//    head    0    1    [2]   3
CMyList::Iterator CMyList::insert(CMyList::Iterator position, const T_LIST int & val){
    if (position.m_pNode == nullptr) {
        return position;
    }

    CMyNode* pNew = new CMyNode(val);

    CMyNode* pPre = position.m_pNode->m_pPre;

    pNew->m_pPre = pPre;
    pNew->m_pNext = position.m_pNode;

    pPre->m_pNext = pNew;
    position.m_pNode->m_pPre = pNew;
    m_nSize++;

    return pNew;
}


//    head    0    1    [2]   3
//    head    0    1    3
CMyList::Iterator CMyList::erase(CMyList::Iterator position){
    if (position.m_pNode == nullptr) {
        return position;
    }

    CMyNode* pPre = position.m_pNode->m_pPre;
    CMyNode* pNext = position.m_pNode->m_pNext;

    pPre->m_pNext = pNext;
    if (pNext != nullptr) {
        pNext->m_pPre = pPre;
    }

    delete position.m_pNode;
    m_nSize--;

    return pNext;
}

//    head    0    1    3
//    head    3    1    0
void CMyList::reverse(){
    if (m_nSize <= 1) {
        return;
    }
    CMyNode* pPre = nullptr;
    CMyNode* pNext = nullptr;

    //表示拿到头结点
    CMyNode* pFront = m_pHead->m_pNext;
    CMyNode* pCur = pFront->m_pNext;

    pFront->m_pNext = nullptr;
    pFront->m_pPre = pCur;

    while(pCur->m_pNext != nullptr){
        pPre = pCur->m_pPre;
        pNext = pCur->m_pNext;

        pCur->m_pPre = pNext;
        pCur->m_pNext = pPre;

        pCur = pNext;
    }

    //到这里，pCur表示的是尾节点
    pCur->m_pNext = pCur->m_pPre;
    pCur->m_pPre = m_pHead;

    m_pHead->m_pNext = pCur;
}
