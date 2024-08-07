
## **类型萃取的后缀 `_v`**

在 C++14 中提出了变量模板，C++17 在标准库中定义了很多变量模板来简化类型萃取的实现，如下：

```cpp
template <class>
constexpr bool is_const_v = false; 

template <class _Ty>
constexpr bool is_const_v<const _Ty> = true;
```

这样在类型萃取时就可以写为 `std::is_const_v<T>` ，而不是 `std::is_const<T>::value`。

## **Fold 表达式**

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


## **类模板的模板实参推导**

在 C++17 前，使用类模板时都必须显式的指出所有的模板参数的类型（除非他们有默认值），在 C++17 开始，这一要求不在那么严格，**如果构造函数能够推断出所有的模板参数的类型**（对于那些没有默认值的模板参数），就不再需要显示的指明模板参数的类型。如下例：

```cpp
std::vector a = { 1,2,3 };
// 在 C++14 报错：缺少类模板 "std::vector" 的参数列表
```

类型实参可以推导，那么推导非类型模板也就不成问题了，如下：

```cpp
template<class Tp,size_t N>
struct CountOf
{
    CountOf(Tp(&)[N]) { }
    const static size_t value = N;
};

int main()
{
    char a[20];
    CountOf c(a);
    std::cout << c.value << '\n';
    return 0;
}
/*
运行结果：
20
*/
```

除了推导非类型模板的数值，C++17 以后也允许我们使用 `auto` 和 `decltype` 作为模板形参，让编译器推导非类型模板的类型：

```cpp
template<class Tp,auto N>
struct Container
{
    using size_type = decltype(N);
    size_type sz = N;
};
Container<int, 20u> c; // size_type 为 unsigned int
```

在通过构造函数推导模板参数时，会优先使用拷贝构造（如果可以拷贝构造的话）：

```cpp  
std::vector a{ 1,2,3 }; // a 为 std::vector<int>
std::vector b{ a };     // b 也为 std::vector<int>
```

要注意的是与函数模板不同，类模板无法部分的推断模板类型参数，也就是说当显示的指定了一部分类模板参数的情况下，是不能推断其他的模板类型参数的。

### **推断指引（Deduction Guides）**

在 C++17 中，当创建一个模板类时，可以通过 推断指引 来提供额外的模板参数推断规则，或修正已有的模板参数推断规则。

我们思考下面这样一个场景，我们想设计一个栈模板，于是我们写下如下代码：

```cpp
template<class Tp>
struct Stack
{
    std::vector<Tp>vec;
public:
    Stack() = default;
    Stack(const Tp& elem)   // 单个元素初始化栈
        : vec{ elem }
    { }
};
```

但是当我们使用一个字符串字面量初始化栈时，如下：

```cpp
Stack a{"Hello World"};
```

我们期望我们的容器类 `Stack` 的类型推导为一个 `char` 类型的指针，而这里却推导成了字符数组类型：

```cpp
Stack<char[12]>
```

这导致我们无法再插入其他长度的字符串，这并不是我们希望的。导致这样的原因就是因为构造函数为**引用传值**，在模板类型推导时无法进行类型退化，使字符串数组类型退化为指针。

解决方法有两种：

- 参数改用按值传递：

```cpp
Stack(Tp elem)
    : vec{ elem }
{ }
```

- 使用**推断指引**，它的语法如下：

```cpp
// 非模板推导指引
ClassName(...) -> ClassName<...>;

// 模板推断指引
template <typename ...Args>
ClassName(Args...) -> ClassName<deduced_types>;
```


在这个例子里，它需要写成这样：

```cpp
template<class Tp>
Stack(Tp) -> Stack<Tp>;
```

这句推导指引的意思是：当构造 `Stack` 类接收到任意一个类型时，我们应当使用其值类型进行模板类型的推导，而不是使用类型的引用进行推导。要注意的是这个指引语句必须出现在和模板类定义相同的作用域或命名空间内。

#### **变参推断指引**

推断指引也可以和可变模板参数结合在一起，如下是STL 库中为 `std::array` 定义的一个推导指引：

```cpp
namespace std {
    template<class Tp, class ...Tps> array(Tp, Tps...)
        ->array<
            enable_if_t<(is_same_v<Tp, Tps> and ...), Tp>, 
            (1 + sizeof...(Tps))
        >;
}
```

它实现了这样的数组初始化：

```cpp
std::array arr{ 1,1,4,5,1,4 };
```

同时他会进行类型检查，保证所有的类型都相同。
