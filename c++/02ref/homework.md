1. 分别使用C和C++编译下面的代码，看看有什么区别，为什么?

```
#include "stdafx.h"

struct bird{
    int nBird;
};

struct rock{
    int rock;
};

void main(){
    bird* b;
    rock* r;
    void* v;
    v = r;
    b = v;
}
```

2. 将下面的代码放入到main中，在输出时增加一些说明，以证明引用就相当于被自动间接引用的指针。

```
#include <iostream>
using namespace std;

// Ordinary free-standing reference:
int y;
int& r = y;
// When a reference is created, it must
// be initialized to a live object.
// However, you can also say:
const int& q = 12; // (1)
// References are tied to someone else's storage:
int x = 0; // (2)
int& a = x; // (3)
int main() {
  cout << "x = " << x << ", a = " << a << endl;
  a++;
  cout << "x = " << x << ", a = " << a << endl;
} ///:~
```

3. 写一个程序，在其中尝试以下操作：
   (1)创建一个引用，在其创建时没有被初始化。
 （2)在一个引用被初始化后，改变它的指向，使之指向另一个对象。
 （3)创建一个NULL引用。
4. 写一个函数，该函数使用指针作为参数，修改指针所指内容，然后用引用返回指针所指的内容。
5. 创建一个函数，使之参数为一个指向指针的指针的引用，要求该函数对其参数进行修改。然后，在main()中调用这个函数。
6. 创建一个函数，使其用char&作参数并修改该参数。在main()函数里，打印一个char变量，使用这个变量做参数，调用我们设计的函数。然后，再次打印此变量以证明它已被改变。请问这影响了程序的可读性吗？
7. 使用下面的宏扩展在使用的时候是否存在问题，请举例说明：
```
#define X(n) ((n)+(n+1))
```
8.创建两个功能相同的函数f1()和f2()，f1()是内联函数，f2()是非内联函数。使用<ctime>中的标准C库函数clock()标记这两个函数的开始点和结束点，比较它们看哪一个运行得更快，为了得到有效的数字，也许需要在计时循环中重复调用这两个函数。
9.举例说明何时使用函数默认参及使用时需要注意的什么。
