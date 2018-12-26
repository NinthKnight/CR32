#include "stdafx.h"
#include "MyTree.h"
#include <queue>
#include <stack>

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

    //��ʾ����߲�������
    while (true) {
        
        if (pCurNode->m_data > data) {
            //ѡ�����
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
            //ѡ���ұ�
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
            //��ʾ����
            while (pCurNode->m_pNext != nullptr) {
                pCurNode = pCurNode->m_pNext;
            }

            //pCurNode->m_pNext  == nullptr
            pCurNode->m_pNext = pNew;
            break;
        }
    }

    Adjust(pCurNode);
    m_nSize++;
    return;
}

bool CMyTree::Delete(int data)
{
    CMyTreeNode * pFind = Find(data);
    if (pFind == nullptr) {
        return false;
    }

    return Delete(pFind);
}


/*
          50
      45      75
    30    55       80
        53  60  78    90
                  79              
          50
            75
          55

          
*/ 
bool CMyTree::Delete(CMyTreeNode * pNode)
{
    if (pNode->m_pLeft == nullptr && pNode->m_pRight == nullptr) {
        //û�ж���

        if (pNode->m_pParent == nullptr) {
            m_pRoot = nullptr;
        }
        else {
            if (pNode->m_pParent->m_pLeft == pNode) {
                pNode->m_pParent->m_pLeft = nullptr;
            }
            else {
                pNode->m_pParent->m_pRight = nullptr;
            }
        }
    }
    else if (pNode->m_pLeft != nullptr && pNode->m_pRight != nullptr) {
        //��������
        CMyTreeNode* pCur = pNode->m_pRight;
        while (pCur->m_pLeft != nullptr) {
            pCur = pCur->m_pLeft;
        }

        pNode->m_data = pCur->m_data;
        return Delete(pCur);
    }
    else {
        //��һ������

        if (pNode->m_pLeft != nullptr) {
            //��ʾֻ�������
            if (pNode->m_pParent != nullptr) {
                if (pNode->m_pParent->m_pLeft == pNode) {
                    pNode->m_pParent->m_pLeft = pNode->m_pLeft;
                }
                else {
                    pNode->m_pParent->m_pRight = pNode->m_pLeft;
                }
            }
            else {
                m_pRoot = pNode->m_pLeft;
            }

            pNode->m_pLeft->m_pParent = pNode->m_pParent;

        }
        else {
            if (pNode->m_pParent != nullptr) {
                //��ʾֻ���Ҷ���
                if (pNode->m_pParent->m_pLeft == pNode) {
                    pNode->m_pParent->m_pLeft = pNode->m_pRight;
                }
                else {
                    pNode->m_pParent->m_pRight = pNode->m_pRight;
                }
            }
            else {
                m_pRoot = pNode->m_pRight;
            }

            pNode->m_pRight->m_pParent = pNode->m_pParent;
        }


    }

    Adjust(pNode->m_pParent);
    delete pNode;
    m_nSize--;

    return false;
}

CMyTree::CMyTreeNode * CMyTree::Find(int data)
{
    CMyTreeNode* pCur = m_pRoot;

    while (pCur != nullptr){
        
        if (pCur->m_data > data) {
            pCur = pCur->m_pLeft;
        }
        else if (pCur->m_data < data) {
            pCur = pCur->m_pRight;
        }
        else {
            return pCur;
        }
    }

    return nullptr;
}

/*
    50  
       60         ==>      60
          70            50    70

       50                                90
   30       90         ==>         50         100
         80    100              30    80          120
                  120

   pG                       pG
     pK1                       pK2
   A     pK2       ==>     pK1      C
       B     C           A    B

*/

void CMyTree::LeftRotate(CMyTreeNode* pK1, CMyTreeNode* pK2){

    CMyTreeNode* pG = pK1->m_pParent;
    CMyTreeNode* pA = pK1->m_pLeft;
    CMyTreeNode* pB = pK2->m_pLeft;
    CMyTreeNode* pC = pK2->m_pRight;

    pK2->m_pParent = pG;
    pK2->m_pLeft = pK1;

    pK1->m_pParent = pK2;
    pK1->m_pRight = pB;

    if (pB != nullptr) {
        pB->m_pParent = pK1;
    }
    
    if (pG != nullptr) {
        if (pG->m_pLeft == pK1) {
            pG->m_pLeft = pK2;
        }
        else {
            pG->m_pRight = pK2;
        }
    }
    else {
        m_pRoot = pK2;
    }

    //����pK1��pK2�ĸ߶�
    pK1->m_nHeight = std::max(GetHeight(pA), GetHeight(pB)) + 1;
    pK2->m_nHeight = std::max(GetHeight(pK1), GetHeight(pC)) + 1;
}

/*
   pG                       pG
      pK1                       pK2
   pK2    A        ==>         B    pK1
  B   C                            C    A
*/

void CMyTree::RightRotate(CMyTreeNode* pK1, CMyTreeNode* pK2)
{
    CMyTreeNode* pG = pK1->m_pParent;
    CMyTreeNode* pA = pK1->m_pRight;
    CMyTreeNode* pB = pK2->m_pLeft;
    CMyTreeNode* pC = pK2->m_pRight;

    pK2->m_pParent = pG;
    pK2->m_pRight = pK1;

    pK1->m_pParent = pK2;
    pK1->m_pLeft = pC;

    if (pC != nullptr) {
        pC->m_pParent = pK1;
    }

    if (pG != nullptr) {
        if (pG->m_pLeft == pK1) {
            pG->m_pLeft = pK2;
        }
        else {
            pG->m_pRight = pK2;
        }
    }
    else {
        m_pRoot = pK2;
    }

    //����pK1��pK2�ĸ߶�
    pK1->m_nHeight = std::max(GetHeight(pA), GetHeight(pC)) + 1;
    pK2->m_nHeight = std::max(GetHeight(pK1), GetHeight(pB)) + 1;

}

bool CMyTree::Adjust(CMyTreeNode * pNode)
{
    CMyTreeNode* pK1 = nullptr;
    CMyTreeNode* pK2 = nullptr;
    CMyTreeNode* pK3 = nullptr;

    while (pNode != nullptr)
    {
        pK1 = pNode;
        pNode->m_nHeight = std::max(GetHeight(pNode->m_pLeft), GetHeight(pNode->m_pRight)) + 1;

        int nSubHeight = GetHeight(pNode->m_pLeft) - GetHeight(pNode->m_pRight);

        if (std::abs(nSubHeight) > 1) {
            if (nSubHeight > 1) {
                pK2 = pK1->m_pLeft;
            }
            else {
                pK2 = pK1->m_pRight;
            }

            if (GetHeight(pK2->m_pLeft) - GetHeight(pK2->m_pRight) > 0) {
                pK3 = pK2->m_pLeft;
            }
            else {
                pK3 = pK2->m_pRight;
            }

            //��ʼ��ת
            //�ж�4�����
            //����
            /*
                pK1
                   pK2
                      pK3
            */
            if (pK2 == pK1->m_pRight && pK3 == pK2->m_pRight){
                LeftRotate(pK1, pK2);
            }


            //�ҵ���
            /*
                      pK1
                   pK2
                pK3
            */
            if (pK2 == pK1->m_pLeft && pK3 == pK2->m_pLeft) {
                RightRotate(pK1, pK2);
            }

            //����˫��
            /*
                pK1
                   pK2
                pK3
            */
            if (pK2 == pK1->m_pRight && pK3 == pK2->m_pLeft){
                RightRotate(pK2, pK3);
                LeftRotate(pK1, pK3);
            }

            //����˫��
            /*
                pK1
             pK2
                pK3
            */
            if (pK2 == pK1->m_pLeft && pK3 == pK2->m_pRight) {
                LeftRotate(pK2, pK3);
                RightRotate(pK1, pK3);
            }
        }

        pNode = pNode->m_pParent;
    }

    return true;
}

void CMyTree::Layer(){
    /*
           50
      30       70
    10  40   60   80

    �洢��                   ���
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
        
        //�ڵ�����в���ӡ
        CMyTreeNode* pNode = que.front();
        printf("%d ", pNode->m_data);
        que.pop();

        //ѹ������Ӻ��Ҷ���
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
   �ݹ飺
   ��������Ϊ�գ������������
   ����ִ�����в��裺
        (1) ���ʸ���㣻
        (2) ����������������
        (3) ����������������
*/

void CMyTree::DLR(CMyTreeNode* pNode){

    if (pNode == nullptr) {
        return;
    }

    printf("%d ", pNode->m_data);
    DLR(pNode->m_pLeft);
    DLR(pNode->m_pRight);
}

void CMyTree::_DLR(CMyTreeNode * pNode)
{
    /*
           50
      30       70
    10  40   60   80

    50  30  10   40  70  60  80

    ջ�� ����-->����                ���
    50 
    70  30                         50
    70  40  10                     50 30
    70                             50 30 10 40
    80  60                         50 30 10 40 70
                                   50 30 10 40 70 60 80
   */

    std::stack<CMyTreeNode*> stk;

    if (pNode == nullptr) {
        return;
    }

    stk.push(pNode);

    while (!stk.empty()) {
    
        CMyTreeNode* pCur = stk.top();
        printf("%d ", pCur->m_data);
        stk.pop();

        if (pCur->m_pRight != nullptr) {
            stk.push(pCur->m_pRight);
        }

        if (pCur->m_pLeft != nullptr) {
            stk.push(pCur->m_pLeft);
        }
    }

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

//�ǵݹ�����
    /*
           50
      30       70
    10  40   60   80
       35

    10  30  35  40  50  60  70  80

    ջ�� ����-->����                ���
    50
    50  30
    50  30  10
    50  30                         10
    50                             10  30
    50  40  35                     10  30
    50  40                         10  30  35
    70  60                         10  30  35  40  50
    70                             10  30  35  40  50  60 
    80                             10  30  35  40  50  60  70
                                   10  30  35  40  50  60  70  80
   */
void CMyTree::_LDR(CMyTreeNode * pNode)
{

    std::stack<CMyTreeNode*> stk;

    CMyTreeNode* pLeft = pNode;
    
    while (true) {
       
        while (pLeft!= nullptr) {
            stk.push(pLeft);
            pLeft = pLeft->m_pLeft;
        }
        
        if (stk.empty()) {
            return;
        }

        //��ʾ�Ѿ��ҵ������
        CMyTreeNode* pCur = stk.top();
        printf("%d ", pCur->m_data);
        stk.pop();

        pLeft = pCur->m_pRight;
    }
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

//�ǵݹ����
    /*
              50
        30        70
     10    40   60   80

    10  40  30  60  80  70  50
    ջ�� ����-->����                ���
    50  30   10
    50  30                         10
    50  30   40                    10   
    50  30                         10  40
    50                             10  40  30
    50  70  60                     10  40  30
    50  70                         10  40  30  60
    50  70  80                     10  40  30  60
    50  70                         10  40  30  60  80
    50                             10  40  30  60  80  70
                                    10  40  30  60  80  70  50


    */
void CMyTree::_LRD(CMyTreeNode * pNode)
{
    std::stack<CMyTreeNode*> stk;

    CMyTreeNode* pLeft = pNode;
    CMyTreeNode* pPre = nullptr;

    while (true) {

        while (pLeft != nullptr) {
            stk.push(pLeft);
            pLeft = pLeft->m_pLeft;
        }

        if (stk.empty()) {
            return;
        }

        //��ʾ�Ѿ��ҵ������
        CMyTreeNode* pCur = stk.top();

        if (pCur->m_pRight == nullptr) {
            printf("%d ", pCur->m_data);
            stk.pop();
            pPre = pCur;
        }
        else {
            if (pPre == pCur->m_pRight) {
                printf("%d ", pCur->m_data);
                stk.pop();
                pPre = pCur;
            }
            else {
                pLeft = pCur->m_pRight;
            }
           
        }

    }
}
