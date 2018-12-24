#include "stdafx.h"
#include "MyTree.h"
#include <queue>

CMyTree::CMyTree(){

    m_pRoot = nullptr;
    m_nSize = 0;
}


CMyTree::~CMyTree()
{
}

/*
        50
      45  55
*/

void CMyTree::Insert(int data){
    CMyTreeNode* pNew = new CMyTreeNode(data);

    if (m_nSize == 0) {
        m_pRoot = pNew;
        m_nSize++;
        return;
    }

    CMyTreeNode* pCurNode = m_pRoot;

    //表示往左边插入数据
    while (true) {
        
        if (pCurNode->m_data > data) {
            //选择左边
            if (pCurNode->m_pLeft == nullptr){
                pCurNode->m_pLeft = pNew;
                pNew->m_pParent = pCurNode;
                break;
            }
            else {
                pCurNode = pCurNode->m_pLeft;
            }

        }
        else if (pCurNode->m_data < data) {
            //选择右边
            if (pCurNode->m_pRight == nullptr) {
                pCurNode->m_pRight = pNew;
                pNew->m_pParent = pCurNode;
                break;
            }
            else {
                pCurNode = pCurNode->m_pRight;
            }
        }
        else {
            //表示等于
            while (pCurNode->m_pNext != nullptr) {
                pCurNode = pCurNode->m_pNext;
            }

            //pCurNode->m_pNext  == nullptr
            pCurNode->m_pNext = pNew;
            break;
        }
    }

    m_nSize++;
    return;
}

void CMyTree::Layer(){
    /*
           50
      30       70
    10  40   60   80

    存储：                   输出
    50               
    30  70                  50
    70  10  40              50  30
    10  40  60  80          50  30  70
    40  60  80              50  30  70 10
                            50  30  70 10 40 60 80
   */

    if (m_nSize == 0) {
        return;
    }

  
    std::queue<CMyTreeNode*> que;
    que.push(m_pRoot);

    while (!que.empty()) {
        
        //节点出队列并打印
        CMyTreeNode* pNode = que.front();
        printf("%d ", pNode->m_data);
        que.pop();

        //压入左儿子和右儿子
        if (pNode->m_pLeft != nullptr) {
            que.push(pNode->m_pLeft);
        }

        if (pNode->m_pRight != nullptr) {
            que.push(pNode->m_pRight);
        }
    }
    printf("\r\n");
}

/*
   递归：
   若二叉树为空，则遍历结束；
   否则，执行下列步骤：
        (1) 访问根结点；
        (2) 遍历根的左子树；
        (3) 遍历根的右子树。
*/

void CMyTree::DLR(CMyTreeNode* pNode){

    if (pNode == nullptr) {
        return;
    }

    printf("%d ", pNode->m_data);
    DLR(pNode->m_pLeft);
    DLR(pNode->m_pRight);
}

void CMyTree::LDR(CMyTreeNode * pNode)
{
    if (pNode == nullptr) {
        return;
    }

    LDR(pNode->m_pLeft);
    printf("%d ", pNode->m_data);
    LDR(pNode->m_pRight);
}

void CMyTree::LRD(CMyTreeNode * pNode)
{
    if (pNode == nullptr) {
        return;
    }

    LRD(pNode->m_pLeft);
    LRD(pNode->m_pRight);
    printf("%d ", pNode->m_data);
}
