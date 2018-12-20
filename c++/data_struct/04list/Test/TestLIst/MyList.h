#pragma once

#define T_LIST
#include <stdexcept>

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
    class Iterator {
        friend class CMyList;
    public:
        Iterator(CMyNode* pNode) {
            m_pNode = pNode;
        }

        bool operator==(Iterator& obj) {
            return m_pNode == obj.m_pNode;
        }

        bool operator!=(Iterator& obj) {
            return m_pNode != obj.m_pNode;
        }

        T_LIST int& operator*() {
            return m_pNode->m_data;
        }

        T_LIST int* operator->() {
            return &m_pNode->m_data;
        }

        Iterator& operator++() {
            //++i;
            m_pNode = m_pNode->m_pNext;
            return (*this);
        }

        Iterator operator++(int) {
            //i++;
            Iterator it = m_pNode;
            m_pNode = m_pNode->m_pNext;

            return it;
        }

    private:
        CMyNode* m_pNode;
    };

public:
    CMyList();
    ~CMyList();

    void push_back(const T_LIST int& n);
    void push_front(const T_LIST int& n);

    void pop_front();
    void pop_back();

    Iterator insert(Iterator position, const T_LIST int& val);
    Iterator erase(Iterator position);

    void reverse();

    T_LIST int front() {
        if (m_nSize == 0) {
            throw std::range_error("m_nSize == 0");
        }

        return m_pHead->m_pNext->m_data;
    }

    T_LIST int back() {
        if (m_nSize == 0) {
            throw std::range_error("m_nSize == 0");
        }

        CMyNode* tmp = m_pHead;
        while (tmp->m_pNext != nullptr) {
            tmp = tmp->m_pNext;
        }

        return tmp->m_data;
    }

    Iterator begin() {
        return m_pHead->m_pNext;
    }

    Iterator end() {
        return nullptr;
    }

    bool empty() const {
        return m_nSize == 0;
    }

    int size() const {
        return m_nSize;
    }

private:
    CMyNode* m_pHead; //表示头结点
    int m_nSize;
};

