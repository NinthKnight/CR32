#pragma once

#define T_LIST



//回文序列 abcdcba


class CMyList
{
private:
    struct CMyNode {
        CMyNode(T_LIST int data) {
            m_data = data;
            m_pNext = nullptr;
            m_pPre = nullptr;
        }

        CMyNode* m_pNext;
        CMyNode* m_pPre;
        T_LIST int m_data;
    };

public:
    CMyList();
    ~CMyList();

    void push_back(const T_LIST int& n);
    void push_front(const T_LIST int& n);
    void pop_front();
    void pop_back();
    iterator insert(iterator position, const value_type& val);
    iterator erase(iterator position);
    reference front();
    reference back();

    iterator begin();
    iterator end();

    bool empty() const;
    size_type size() const;
    void reverse();




private:
    CMyNode* m_pHead; //表示头结点
    int m_nSize;
};

