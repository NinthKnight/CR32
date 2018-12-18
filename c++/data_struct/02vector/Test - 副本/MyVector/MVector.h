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

    //����
    void push_back(const int& val) throw(std::bad_alloc);

    //����
    void pop_back() throw(std::range_error);

    //����
    void insert(Iterator it, const int& val) throw(std::bad_alloc, std::range_error);

    //ɾ��
    void erase(Iterator it);

    //�޸�
    int& operator[](int nIndex);

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

    int* m_pData;
    int  m_nSize; //��ʾ��ǰ����Ԫ�صĸ���
    int  m_nCapacity; //��ʾ����������

};

