// TestTree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "MyTree.h"

/*
           50
      30       70
    10  40   60   80

    10 40 30 60 80 70 50
*/

void foo() {
    CMyTree tree;

    tree.Insert(50);
    tree.Insert(30);
    tree.Insert(70);
    tree.Insert(10);
    tree.Insert(40);
    tree.Insert(60);
    tree.Insert(80);

    //层序遍历
    //tree.Delete(10);
    //tree.LDR(tree.GetRoot());
    //printf("\r\n");
    //tree.Delete(30);
    //tree.LDR(tree.GetRoot());
    //printf("\r\n");
    tree.Delete(50);
    tree.LDR(tree.GetRoot());

    //前序遍历
    //50  30  10 40 70 60 80
    //tree._DLR(tree.GetRoot());

    //中序遍历
    //10 30 40 50 60 70 80
    //tree._LDR(tree.GetRoot());

    /*
          30
        10  40
      : 10 30 40        
      
          40
        30
      10
      : 10 30 40
    */

    //tree.LDR(tree.GetRoot());

    //后序遍历
    //10 40 30 60 80 70 50
    //tree._LRD(tree.GetRoot());

}

int main()
{
    //9+2*3+8/4




    foo();

    return 0;
}

