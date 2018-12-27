#pragma once

//����������
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
		bool m_color;   //��ɫ:true ��ɫ:false 
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

	//���ֻ�������ת
	//����
	CMyTreeNode* LeftRotate(CMyTreeNode* pNode);

	//����
	CMyTreeNode* RightRotate(CMyTreeNode* pNode);

	//һ�ֲ���Ҫ��ת��ֻ��Ҫ�ı���ɫ
	void flipColors(CMyTreeNode* pNode);

	//���������
	void Adjust(CMyTreeNode* pNode);

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

