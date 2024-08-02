


## **带初始化的 `if` 语句**

语法如下：

```cpp
if ( init-statement(optional); condition )
```

C++17 提供的语法糖，允许我们在 `if` 语句中加一个初始化表达式，类似 `for` 循环的第一个部分，下面是一些例子：

```cpp
if(int i = 1; (x << i) < 10)
{
    // do something...
}
```

## **编译其 `if`**

C++17 以后可以定义编译期求值的 `if` 语句，语法如下：

```cpp
if constexpr (condition) /*statement-true*/ else /*statement-false*/	
```

这样可以简化一些编译器求值的代码，我们以模板参数包展开为例:

```cpp
template<class Tp,class ...Args>
void print(Tp a, Args... args)
{
    std::cout << a << std::endl;
    if constexpr (sizeof...(args) > 0)
        print(args...);
}
```

在 C++17 以前，要实现这样的功能就要写一个空参数版本的 `print` ，来作为出口。
