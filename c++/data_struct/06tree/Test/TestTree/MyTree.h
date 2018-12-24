#pragma once

//����������
/*
        50
      45  55

*/

class CMyTree
{
public:
    struct CMyTreeNode {
        CMyTreeNode(int data = 0) {
            m_pParent = nullptr;
            m_pLeft = nullptr;
            m_pRight = nullptr;
            m_pNext = nullptr;
            m_data = data;
        }

        int m_data;
        CMyTreeNode* m_pParent;
        CMyTreeNode* m_pLeft;
        CMyTreeNode* m_pRight;
        CMyTreeNode* m_pNext;
    };

public:
    CMyTree();
    ~CMyTree();

    /*
            A
        B       C
      D      F    G
    
    A B D E C F G
    A B C D ? F G
  
    */

    //��
    void Insert(int data);

    //ɾ

    //��

    //��

    CMyTreeNode* GetRoot() {
        return m_pRoot;
    }

    //������4��
    //1. ����
    void Layer();

    //2. ǰ��
    void DLR(CMyTreeNode* pNode);

    //3. ����
    void LDR(CMyTreeNode* pNode);

    //4. ����
    void LRD(CMyTreeNode* pNode);

private:
    CMyTreeNode* m_pRoot;
    int m_nSize;//��ʾ�ڵ���ܸ���
};

