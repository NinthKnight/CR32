#pragma once

//二叉排序树
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

    //增
    void Insert(int data);

    //删

    //改

    //查

    CMyTreeNode* GetRoot() {
        return m_pRoot;
    }

    //遍历：4种
    //1. 层序
    void Layer();

    //2. 前序
    void DLR(CMyTreeNode* pNode);

    //3. 中序
    void LDR(CMyTreeNode* pNode);

    //4. 后序
    void LRD(CMyTreeNode* pNode);

private:
    CMyTreeNode* m_pRoot;
    int m_nSize;//表示节点的总个数
};

