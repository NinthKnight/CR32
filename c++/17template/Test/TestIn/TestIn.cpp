// TestIn.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

//内部类
template <typename T>
class CMyList {
public:
    template <typename T>
    class CMyItem {

    private:
        T m_nInt;
    };

    CMyItem<T>& GetFirstItem();

private:
    CMyItem<T> m_item[100];
};

template <typename T>
typename CMyList<T>::CMyItem<T>& CMyList<T>::GetFirstItem() {
    return m_item[0];
}

int main()
{
    CMyList<int> lst;

    CMyList<int>::CMyItem<int> it = lst.GetFirstItem();



    return 0;
}

