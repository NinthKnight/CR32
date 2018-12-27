#pragma once

//二叉排序树
/*
        50
      45  55

*/
#define RED true
#define BLACK false

#define max(a,b) (((a) > (b)) ? (a) : (b))

class CMyTree
{

public:
    struct CMyTreeNode {
        CMyTreeNode(int data = 0, bool color = RED) {
            m_pParent = nullptr;
            m_pLeft = nullptr;
            m_pRight = nullptr;
            m_pNext = nullptr;
            m_data = data;

			m_nHeight = 0;
			m_color = color;
        }

        int m_data;
        CMyTreeNode* m_pParent;
        CMyTreeNode* m_pLeft;
        CMyTreeNode* m_pRight;
        CMyTreeNode* m_pNext;

		int m_nHeight;
		bool m_color;   //红色:true 黑色:false 
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

	bool IsRed(CMyTreeNode* pNode) {
		if (pNode == nullptr) {
			return BLACK;
		}

		return pNode->m_color;
	}

	int  GetHeight(CMyTreeNode* pNode){
		return pNode == NULL ? 0 : pNode->m_nHeight;
	}

	//两种基本的旋转
	//左旋
	CMyTreeNode* LeftRotate(CMyTreeNode* pNode);

	//右旋
	CMyTreeNode* RightRotate(CMyTreeNode* pNode);

	//一种不需要旋转，只需要改变颜色
	void flipColors(CMyTreeNode* pNode);

	//调整红黑树
	void Adjust(CMyTreeNode* pNode);

    //增
    void Insert(int data);

    //删
    bool Delete(int data);
    bool Delete(CMyTreeNode* pNode);

    //改
    //bool Set(int data, int change);

    //查
    CMyTreeNode* Find(int data);

    CMyTreeNode* GetRoot() {
        return m_pRoot;
    }

    //遍历：4种
    //1. 层序
    void Layer();

    //2. 前序
    void DLR(CMyTreeNode* pNode);
    //非递归前序
    void _DLR(CMyTreeNode* pNode);

    //3. 中序
    void LDR(CMyTreeNode* pNode);

    //非递归中序
    void _LDR(CMyTreeNode* pNode);

    //4. 后序
    void LRD(CMyTreeNode* pNode);

    //非递归后序
    void _LRD(CMyTreeNode* pNode);

private:
    CMyTreeNode* m_pRoot;
    int m_nSize;//表示节点的总个数
};

