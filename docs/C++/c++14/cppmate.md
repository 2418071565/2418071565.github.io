

## **泛型 lambda 表达式**

C++14 引入了泛型 lambda 表达式，它的写法如下：

```cpp
auto f = [](auto a, auto b) {
    return a + b;
};
```

就是再 lambda 中使用 `auto` 关键字，它会在编译时生成如下成员模板：

```cpp
class lambdaName {
public:
    template<class Tp1,class Tp2>
    auto operator()(Tp1 a, Tp2 b) const {
        return a + b;
    }
};
```

## **变量模板**

C++14 开始，变量也可以被某种类型参数化，引入变量模板的主要目的是为了简化定义（simplify definitions）以及对模板化常量（parameterized constant）的支持。

通过以下代码定义了一个参数化类型的 $\pi$：

```cpp
template<class Tp>
constexpr Tp pi = 3.1415926 ;
```

使用它时要指定 $\pi$ 的类型：

```cpp
std::cout << pi<int> << std::endl;      // 3
std::cout << pi<double> << std::endl;   // 3.1415926
```

变量模板也可以是非类型模板，如下：

```cpp
template<size_t N>
std::array<int, N> arr{};
```

使用时给定数组个数，即可：

```cpp
arr<10>[1] = 12;
for (int i = 0; i < arr<10>.size(); ++i)
{
    std::cout << arr<10>[i] << std::endl;
}
```

要注意的是在不同编译单元初始化或使用 `arr` 时，只要模板参数相同，使用的都是同一个 `arr`。


