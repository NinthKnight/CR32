// TestTree.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "MyTree.h"

/*
		
*/

void foo() {
    CMyTree tree;

    tree.Insert(3);
    tree.Insert(1);
    tree.Insert(9);
    tree.Insert(10);

	tree.Layer();


}

int main()
{
    foo();

    return 0;
}

