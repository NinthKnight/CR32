0. 请结合实际的例子说明volatile关键字的作用。
1. 请结合实际例子说明命名空间的使用及原理。
2.创建一个包含一个名字空间的头文件。在名字空间里声明几个函数。再创建另一个头文件，它包含第一个头文件，并在先前的名字空间的基础上再增加几个函数声明。写一个包含第二个头文件的cpp文件。把名字空间用一个短的别名代替。在函数定义里使用作用域运算符调用这些函数。在另外一个单独的函数里，通过using指令把名字空间引入到函数中。并证实：这时并不需要作用域运算符调用名字空间里的函数。
4. 请使用多种方式来引用std命名空间中的cout对象（using namespace std/using std::)。
5. 在文件Arithmetic.cpp中，说明在一个函数中使用的using指令并不能扩展到这个函数的范围之外。

```
//: C10:Arithmetic.cpp
#include "NamespaceInt.h"
void arithmetic() {
  using namespace Int;
  Integer x;
  x.setSign(positive);
}
int main(){} ///:~

```

```
//: C10:NamespaceInt.h
#ifndef NAMESPACEINT_H
#define NAMESPACEINT_H
namespace Int {
  enum sign { positive, negative };
  struct Integer {
    int i;
    sign s;
    sign getSign() const { return s; }
    void setSign(sign sgn) { s = sgn; }
    // ...
  };
}
#endif // NAMESPACEINT_H ///:~
```
1.抽空写一个代码统计工具，：列出代码行数，注释行数，空行行数等
2.用C++将Ascii码表(分别以十进制，字符，十六进制,八进制)输出控制台上。
3.把
```
Menu
===================================
1. Input the students’ names and scores
2. Search scores of some students
3. Modify scores of some students
4. List all students’ scores
5. Quit the system
===================================
Please input your choise (1-5):
-------------------------------------------------------------------------
```
用C++的cout输出
4.用cout 输出float类型的整型形式。
5.用cout 输出类似printf("%d", 浮点数)格式化浮点为整形的方式
6.将2.45分别以整型，单(双)精度浮点,科学表示法输出
