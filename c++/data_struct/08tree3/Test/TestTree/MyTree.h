#pragma once
#include <math.h>
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

            m_nHeight = 1;
        }

        int m_data;
        CMyTreeNode* m_pParent;
        CMyTreeNode* m_pLeft;
        CMyTreeNode* m_pRight;
        CMyTreeNode* m_pNext;

        //��ʾ��ǰ�ڵ�����
        //�սڵ����Ϊ0
        //Ҷ�ӽڵ����Ϊ1
        int m_nHeight; 
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
    bool Delete(int data);
    bool Delete(CMyTreeNode* pNode);

    //��
    //bool Set(int data, int change);

    //��
    CMyTreeNode* Find(int data);

    CMyTreeNode* GetRoot() {
        return m_pRoot;
    }

    int GetHeight(CMyTreeNode* pNode) {
        if (pNode == nullptr) {
            return 0;
        }

        return pNode->m_nHeight;
    }

    //����
    void LeftRotate(CMyTreeNode* pK1, CMyTreeNode* pK2);

    //����
    void RightRotate(CMyTreeNode* pK1, CMyTreeNode* pK2);

    //ִ��ƽ��Ĳ���
    bool Adjust(CMyTreeNode* pNode);


    //������4��
    //1. ����
    void Layer();

    //2. ǰ��
    void DLR(CMyTreeNode* pNode);
    //�ǵݹ�ǰ��
    void _DLR(CMyTreeNode* pNode);

    //3. ����
    void LDR(CMyTreeNode* pNode);

    //�ǵݹ�����
    void _LDR(CMyTreeNode* pNode);

    //4. ����
    void LRD(CMyTreeNode* pNode);

    //�ǵݹ����
    void _LRD(CMyTreeNode* pNode);

private:
    CMyTreeNode* m_pRoot;
    int m_nSize;//��ʾ�ڵ���ܸ���
};

