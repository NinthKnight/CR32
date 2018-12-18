#pragma once

#include <new>  
#include <stdexcept>

#define VECTOR_CAPACITY 10


class CMyVector
{
public:
    class Iterator {
        friend class CMyVector;
    public:
        Iterator(int* p) {
            m_ptr = p;
        }

        bool operator==(Iterator& obj) {
            return m_ptr == obj.m_ptr;
        }

        bool operator!=(Iterator& obj) {
            return m_ptr != obj.m_ptr;
        }

        int& operator*() {
            return *m_ptr;
        }

        int* operator->() {
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
        int* m_ptr;
    };


public:
    CMyVector();
    ~CMyVector();

    //增加
    void push_back(const int& val) throw(std::bad_alloc);

    //弹出
    void pop_back() throw(std::range_error);

    //插入
    void insert(Iterator it, const int& val) throw(std::bad_alloc, std::range_error);

    //删除
    void erase(Iterator it);

    //修改
    int& operator[](int nIndex);

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

    int* m_pData;
    int  m_nSize; //表示当前容器元素的个数
    int  m_nCapacity; //表示容器的容量

};

