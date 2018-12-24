// Comsumer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <memory>
#include "ITask.h"
#include "TaskQueueManager.h"

int main()
{
    //fooType f = []() {
    //    printf("test\r\n");
    //};
    //f();


    TaskQueueManager mgr;

    for (int i = 0; i < 1000; i++) {
        if (i % 2 == 0) {

            fooType fAdd = std::bind([](int n1, int n2) {
                printf("%d + %d = %d\r\n", n1, n2, n1+n2);
            }, i, 1);

            mgr.push(fAdd);
        }
        else {
            fooType fSub = std::bind([](int n1, int n2) {
                printf("%d - %d = %d\r\n", n1, n2, n1 - n2);
            }, i, 0);

            //fSub();
            mgr.push(fSub);
        }
    }
    ////
    mgr.Loop();


    {
        //std::shared_ptr<int> smartPtr(new int(1));

        //std::shared_ptr<int> smartPtr(std::make_shared<int>(1));

        //*smartPtr = 2;


        //std::shared_ptr<ITask> smartPtr(new CAddTask(1, 2));


    }


    return 0;
}

