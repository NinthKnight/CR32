#include "stdafx.h"
#include "MVector.h"



CMyVector::CMyVector()
{
    m_pData = new int[VECTOR_CAPACITY]{0};
    m_nSize = 0;
    m_nCapacity = VECTOR_CAPACITY;
}

CMyVector::~CMyVector()
{
    if (m_pData != nullptr) {
        delete[] m_pData;
        m_pData = nullptr;
    } 

    m_nSize = 0;
    m_nCapacity = 0;
}

void CMyVector::push_back(const int & val)
{
    //�жϿռ��Ƿ��㹻
    if (m_nSize + 1 > m_nCapacity) {
        //��ʾ�ռ�С�ˣ���Ҫ��������ռ�
        m_nCapacity = m_nCapacity + VECTOR_CAPACITY;

        int* pData = new int[m_nCapacity];
        if (pData == nullptr) {
            throw std::bad_alloc();
        }

        //����ԭʼ������
        memcpy(pData, m_pData, m_nSize * sizeof(int));
        delete [] m_pData;
        m_pData = pData;
    }

    //������ռ�϶��ǹ���
    m_pData[m_nSize++] = val;
}

int& CMyVector::operator[](int nIndex)
{
    return m_pData[nIndex];
}
