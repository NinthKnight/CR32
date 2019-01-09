#pragma once

#include <new>  
#include <stdexcept>

#define VECTOR_CAPACITY 10

//Ӧ�ó��ϣ�
// ����ɾ����Ƶ���������ģȷ����
// ����Ԫ�ؿ�

template<typename T>
class CMyVector
{
public:
    class Iterator {
        friend class CMyVector;
    public:
        Iterator(T* p) {
            m_ptr = p;
        }

        bool operator==(Iterator& obj) {
            return m_ptr == obj.m_ptr;
        }

        bool operator!=(Iterator& obj) {
            return m_ptr != obj.m_ptr;
        }

        T& operator*() {
            return *m_ptr;
        }

        T* operator->() {
            return m_ptr;
        }

        Iterator& operator++() {
            //++i;
            ++m_ptr;
            return (*this);
        }

        Iterator operator++(int) {
            //i++;
            return m_ptr++;
        }

        Iterator& operator--() {
            --m_ptr;
            return (*this);
        }

        Iterator operator--(int) {
            return m_ptr--;
        }

        Iterator operator-(int n) {
            return m_ptr - n;
        }



    private:
        T* m_ptr;
    };


public:
    CMyVector();
    ~CMyVector();

    //����
    void push_back(const T& val) throw(std::bad_alloc);

    //����
    void pop_back() throw(std::range_error);

    //����
    void insert(Iterator it, const T& val) throw(std::bad_alloc, std::range_error);

    //ɾ��
    void erase(Iterator it);

    //�޸�
    T& operator[](int nIndex);

    inline int size() {
        return m_nSize;
    }

    //������
public:
    //���ص�0��Ԫ�ص�λ�õĵ�����
    Iterator begin();

    //�������һ��Ԫ�ص�λ�õĵ�����
    Iterator end();

    
private:
    //���ռ��С
    void CheckCapacity();


private:

    T* m_pData;
    int  m_nSize; //��ʾ��ǰ����Ԫ�صĸ���
    int  m_nCapacity; //��ʾ����������
};

template<typename T>
CMyVector<T>::CMyVector()
{
    m_pData = new T[VECTOR_CAPACITY];
    m_nSize = 0;
    m_nCapacity = VECTOR_CAPACITY;
}

template<typename T>
CMyVector<T>::~CMyVector()
{
    if (m_pData != nullptr) {
        delete[] m_pData;
        m_pData = nullptr;
    }

    m_nSize = 0;
    m_nCapacity = 0;
}

template<typename T>
void CMyVector<T>::push_back(const T & val)
{
    CheckCapacity();

    //������ռ�϶��ǹ���
    m_pData[m_nSize++] = val;
}

template<typename T>
void CMyVector<T>::pop_back()
{
    if (m_nSize <= 0) {
        throw std::range_error("m_nSize < 0");
    }

    m_nSize--;
}

template<typename T>
T& CMyVector<T>::operator[](int nIndex)
{
    return m_pData[nIndex];
}

template<typename T>
typename CMyVector<T>::Iterator CMyVector<T>::begin()
{
    return &m_pData[0];
}

template<typename T>
typename CMyVector<T>::Iterator CMyVector<T>::end()
{
    if (m_nSize <= 0) {
        throw std::range_error("m_nSize < 0");
    }

    return &m_pData[m_nSize];
}

template<typename T>
void CMyVector<T>::CheckCapacity()
{
    //�жϿռ��Ƿ��㹻
    if (m_nSize + 1 > m_nCapacity) {
        //��ʾ�ռ�С�ˣ���Ҫ��������ռ�
        m_nCapacity = m_nCapacity + VECTOR_CAPACITY;

        T* pData = new T[m_nCapacity];
        if (pData == nullptr) {
            throw std::bad_alloc();
        }

        //����ԭʼ������
        memcpy(pData, m_pData, m_nSize * sizeof(T));
        delete[] m_pData;
        m_pData = pData;
    }
}

//����
template<typename T>
void CMyVector<T>::insert(Iterator it, const T& val) {

    int nIndex = it.m_ptr - m_pData;

    if (nIndex < 0 || nIndex > m_nSize) {
        throw std::range_error("nIndex < 0");
    }

    CheckCapacity();

    //������ռ�϶��ǹ���
    for (int i = m_nSize; i > nIndex; i--) {
        m_pData[i] = m_pData[i - 1];
    }

    m_pData[nIndex] = val;
    m_nSize++;
}

template<typename T>
void CMyVector<T>::erase(Iterator it)
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
