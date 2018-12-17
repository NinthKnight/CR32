#pragma once

#include <new>  
#define VECTOR_CAPACITY 10
class CMyVector
{
public:
    CMyVector();
    ~CMyVector();

    //增加
    void push_back(const int& val) throw(std::bad_alloc);

    //插入
    void insert(int nIndex, const int& val);

    //删除
    void erase(int nIndex);

    //修改
    int& operator[](int nIndex);

    inline int size() {
        return m_nSize;
    }

private:


    int* m_pData;
    int  m_nSize; //表示当前容器元素的个数
    int  m_nCapacity; //表示容器的容量

};

