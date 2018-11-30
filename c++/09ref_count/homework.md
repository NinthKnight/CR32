* 1 完成C++俄罗斯方块

* 2 写一个类，让这个类只能产生一个对象（单例模式）。

*3 在第二题的基础上，尝试下面的代码：

```
int main(){
    CMystring str = "Hello World!";
    CMystring str2 = str;
    CMystring str3 = str;
    {
        CMystring str4 = str2;
    }
    return 0;
}
```

在上面的程序中，
(1) 如果CMystring使用的是浅拷贝，程序编译能否通过，运行是否有问题，为什么?
(2) 如果CMystring使用的是深拷贝，程序编译能否通过，运行是否有问题？该程序中有多少份"Hello World!"字符串的拷贝？
(3) 能否做到仅有一份"Hello World!"拷贝，而程序仍正常运行，结果不变？思考深拷贝是否存在缺点，并提出解决深拷贝和浅拷贝各自缺点的一种方案（可以使用伪代码描述）。
(4) 结合下面的代码，思考如果仅有一份"Hello World!"的拷贝，会不会引发新的问题，应该如何解决？


```
  int main(){
      CMystring str = "Hello World!";
      CMystring str2 = str;
      CMystring str3 = str;
      {
          CMystring str4 = str2;
      }

      str3.cat("123");

      return 0;
  }
```
