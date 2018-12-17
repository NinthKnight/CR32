#pragma once

#include <new>  
#define VECTOR_CAPACITY 10
class CMyVector
{
public:
    CMyVector();
    ~CMyVector();

    //����
    void push_back(const int& val) throw(std::bad_alloc);

    //����
    void insert(int nIndex, const int& val);

    //ɾ��
    void erase(int nIndex);

    //�޸�
    int& operator[](int nIndex);

    inline int size() {
        return m_nSize;
    }

private:


    int* m_pData;
    int  m_nSize; //��ʾ��ǰ����Ԫ�صĸ���
    int  m_nCapacity; //��ʾ����������

};

