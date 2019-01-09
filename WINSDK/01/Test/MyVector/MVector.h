#pragma once

#include <new>  
#include <stdexcept>

#define VECTOR_CAPACITY 10

//应用场合：
// 插入删除不频繁，问题规模确定的
// 访问元素快

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

    //增加
    void push_back(const T& val) throw(std::bad_alloc);

    //弹出
    void pop_back() throw(std::range_error);

    //插入
    void insert(Iterator it, const T& val) throw(std::bad_alloc, std::range_error);

    //删除
    void erase(Iterator it);

    //修改
    T& operator[](int nIndex);

    inline int size() {
        return m_nSize;
    }

    //迭代器
public:
    //返回第0项元素的位置的迭代器
    Iterator begin();

    //返回最后一项元素的位置的迭代器
    Iterator end();

    
private:
    //检查空间大小
    void CheckCapacity();


private:

    T* m_pData;
    int  m_nSize; //表示当前容器元素的个数
    int  m_nCapacity; //表示容器的容量
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

    //到这里空间肯定是够了
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
    //判断空间是否足够
    if (m_nSize + 1 > m_nCapacity) {
        //表示空间小了，需要重新申请空间
        m_nCapacity = m_nCapacity + VECTOR_CAPACITY;

        T* pData = new T[m_nCapacity];
        if (pData == nullptr) {
            throw std::bad_alloc();
        }

        //拷贝原始的数据
        memcpy(pData, m_pData, m_nSize * sizeof(T));
        delete[] m_pData;
        m_pData = pData;
    }
}

//插入
template<typename T>
void CMyVector<T>::insert(Iterator it, const T& val) {

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
