// TestTree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "MyTree.h"

/*
左旋：

           50
      30       70
    10  40        80
                     90   

===>
           50
      30       80
    10  40  70    90
   
右旋：

           50
      30        70
    10        60  80
  5 

===>
           50
      10        70
    5  30     60  80
*/

//A V L

void foo() {
    CMyTree tree;

    /*
        30              30                50
           70   ==>        50      ==>  30  70
        50                    70
    
       先右单旋，再左单旋

         70                   70             60
      50        ==>         60     ==>     50   70
         60               50
    
       先左单旋，再右单旋
    */


    tree.Insert(53);
    tree.Insert(29);
    tree.Insert(69);
    tree.Insert(11);
    tree.Insert(30);
    tree.Insert(60);
    tree.Insert(86);
    tree.Insert(15);

    tree.Delete(30);

    tree.Layer();

    //层序遍历
    //tree.Delete(10);
    //tree.LDR(tree.GetRoot());
    //printf("\r\n");
    //tree.Delete(30);
    //tree.LDR(tree.GetRoot());
    //printf("\r\n");
    //tree.Delete(50);
    //tree.LDR(tree.GetRoot());

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

