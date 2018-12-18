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
    CheckCapacity();

    //到这里空间肯定是够了
    m_pData[m_nSize++] = val;
}

void CMyVector::pop_back()
{
    if (m_nSize <= 0) {
        throw std::range_error("m_nSize < 0");
    }

    m_nSize--;
}

int& CMyVector::operator[](int nIndex)
{
    return m_pData[nIndex];
}

CMyVector::Iterator CMyVector::begin()
{
    return &m_pData[0];
}

CMyVector::Iterator CMyVector::end()
{
    if (m_nSize <= 0) {
        throw std::range_error("m_nSize < 0");
    }

    return &m_pData[m_nSize];
}

void CMyVector::CheckCapacity()
{
    //判断空间是否足够
    if (m_nSize + 1 > m_nCapacity) {
        //表示空间小了，需要重新申请空间
        m_nCapacity = m_nCapacity + VECTOR_CAPACITY;

        int* pData = new int[m_nCapacity];
        if (pData == nullptr) {
            throw std::bad_alloc();
        }

        //拷贝原始的数据
        memcpy(pData, m_pData, m_nSize * sizeof(int));
        delete[] m_pData;
        m_pData = pData;
    }
}

//插入
void CMyVector::insert(Iterator it, const int& val) {

    int nIndex = it.m_ptr - m_pData;

    if (nIndex < 0 || nIndex > m_nSize) {
        throw std::range_error("nIndex < 0");
    }

    CheckCapacity();

    //到这里空间肯定是够了
    for (int i = m_nSize; i > nIndex; i--) {
        m_pData[i] = m_pData[i - 1];
    }

    m_pData[nIndex] = val;
    m_nSize++;
}

void CMyVector::erase(Iterator it)
{
    //if (nIndex >= m_nSize || m_nSize <= 0 || nIndex < 0) {
    //    throw std::range_error("nIndex >= m_nSize || m_nSize <= 0 || nIndex < 0");
    //}

    //for (int i = nIndex; i < m_nSize - 1; i++)
    //{
    //    m_pData[i] = m_pData[i+1];
    //}

    //m_nSize--;
}
