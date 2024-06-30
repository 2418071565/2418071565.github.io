
## **简介**

[cppreference : fold expressions](https://en.cppreference.com/w/cpp/language/fold){target="_blank"}

C++ 17 提供了一种新的包展开方式，语法有下面四种写法：

不管哪种写法，在展开表达式时，都不会改变参数包中参数的顺序。

- `(... op E)`： `(((E1 op E2) op ...) op EN)`，表达式从左向右展开

-  `(E op ...)`：`(E1 op (... op (EN-1 op EN)))`，表达式从右向左展开

这两种是没有初始值的，语法类似:

```cpp
template<class Tp>
void print(Tp a)
{
	cout << a << ',';
}

template<class... Args>
void unpacker(Args... as)
{
	(print(as), ...);
	cout << '\n';
}
/*
展开结果：
template<>
void unpacker<int, int, char>(int __as0, int __as1, char __as2)
{
  print(__as0) , (print(__as1) , print(__as2));
  std::operator<<(std::cout, '\n');
}
*/
```

- `(E op ... op I)` ： `(E1 op (... op (EN−1 op (EN op I))))`
  
- `(I op ... op E)` ： `((((I op E1) op E2) op ...) op EN)`

有初始值的会先将第一个展开的参数与初始值做 `op` 运算：


```cpp
template<class... Args>
void unpacker(Args... as)
{
	(cout << ... << as) << '\n';
}
/*
展开结果：
template<>
void unpacker<int, int, char>(int __as0, int __as1, char __as2)
{
  std::operator<<(std::operator<<(std::cout.operator<<(__as0).operator<<(__as1), __as2), '\n');
}
*/
```