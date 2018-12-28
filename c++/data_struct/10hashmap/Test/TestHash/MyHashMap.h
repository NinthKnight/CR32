#pragma once
#include <list>


#define HASHMAP_SIZE 32

int hash(int k) {
    return k % HASHMAP_SIZE;
}

class CMyHashMap
{
public:
    struct CMyHashMapNode{
        CMyHashMapNode(int k, int v) {
            KEY = k;
            VALUE = v;
        }

        int KEY;
        int VALUE;

    };


    CMyHashMap() {
        m_nSize = 0;
    }

    ~CMyHashMap();

    //����
    void Insert(int k, int v) {
        int nIndex = hash(k);
        CMyHashMapNode* pNew = new CMyHashMapNode(k, v);
        //������Ҫ�ж�key�����ظ�
        m_Ary[nIndex].push_back(pNew);
        m_nSize++;
    }

    //ɾ��
    void Delete(int k) {
        int nIndex = hash(k);

        for (auto it = m_Ary[nIndex].begin();
            it != m_Ary[nIndex].end();
            it++) {
            if ((*it)->KEY == k) {
                delete (*it);
                m_Ary[nIndex].erase(it);
                m_nSize--;
                break;
            }
        }
    }


    //����
    int Find(int k) {
        int nIndex = hash(k);

        for (auto it = m_Ary[nIndex].begin();
        it != m_Ary[nIndex].end();
            it++) {
            if ((*it)->KEY == k) {
                return (*it)->VALUE;
            }
        }

        return m_tmp.VALUE;
    }

    //�޸�
    int& operator[](int k) {
        int nIndex = hash(k);

        for (auto it = m_Ary[nIndex].begin();
        it != m_Ary[nIndex].end();
            it++) {
            if ((*it)->KEY == k) {
                return (*it)->VALUE;
            }
        }

        return m_tmp.VALUE;
    }

private:

    std::list<CMyHashMapNode*> m_Ary[HASHMAP_SIZE];
    int m_nSize;

    CMyHashMapNode m_tmp;

};

