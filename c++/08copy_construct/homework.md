* 1 举例说明什么是深拷贝及浅拷贝，在何种情况下浅拷贝会有问题，如何避免？

* 2 根据下面的CMystring类的接口，实现对应的函数，特别是实现构造，拷贝构造，析构函数。

```
class CMystring  
{
public:
    /* 返回当前缓冲区大小*/
    inline int GetBufferSize() const;

    /* 返回当前字符串长度*/
    inline int GetStrlen() const;

    /* 格式化字符串，功能类似于printf，但是结果保存在m_pStr中*/
    int Format(const char* strFormat, ...);

    /*
      CMystring str;
      str.Format("%s:%d", "127.0.0.1", "8080");
      "127.0.0.1:8080"
    */

    /* 比较字符串，参考strcmp */
    int Cmp(const char* strSrc) const;
    int Cmp(const CMystring &strCmp) const;

    /* 返回一个缓冲区，其大小最少为nMinBuffLen(可以大于nMinBuffLen)。如果GetBuffer(0)，则返回
    当前缓冲区*/
    char* GetBuffer(int nMinBuffLen);

    /* 获取当前m_pStr
    */
    char* GetStr() const;

    /* 设置CMyString字符串(注意考虑新设置的字符串strSrc大于当前缓冲区的情况)*/
    int SetStr(const char* strSrc);

    /* 连接strCat到当前对象，类似strcat*/
    void Cat(const char* strCat);
    void Cat(const CMystring &strCat);

    /* 初始化自身（已有实现参考）*/
    void InitSelf();
    /* 释放自身（已有实现参考） */
    void ReleaseSelf();

    /* 将字符串全部转为大写 */
    void ToUpper();
    /* 将字符串全部转为小写 */
    void ToLower();

private:
    int m_nBuffLen;
    int m_nStrLen;
    char *m_pStr;

};
```

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
