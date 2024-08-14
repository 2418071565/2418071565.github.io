

## **模板参数模板**

C++11 引入了模板参数模板（Template Template Parameters）。这个特性允许模板参数本身也可以是模板，从而提供了更高的灵活性和抽象能力。以下是一个简单的示例：

```cpp
#include <iostream>
#include <vector>

template <template <typename, typename> class Container, typename T>
void printContainer(const Container<T, std::allocator<T>>& container) {
    for (const auto& elem : container) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    printContainer(vec);
    return 0;
}
```

在这个示例中，`printContainer`函数模板使用了模板参数模板。`Container`是一个模板参数，它本身也是一个模板，接受两个类型参数。通过这种方式，`printContainer`函数模板可以接受像`std::vector`这样的容器模板作为参数。



## **可变参数模板**

C++11 为模板提供定义边长参数的方法，基础语法如下：

```cpp
template<class... Args>
void f (Args... a) { }
```

`Args` 是一个模板参数包，`a` 是一个函数形参参数包。参数包 `a` 会接收任意数量的参数。这里的省略号 `(...)` 在不同位置代表着不同的含义：

- `class... Args`，这里代表模板参数包，表明这里有多种参数。
- `Args... a`，这里代表函数参数包，表明这里有多个参数。
- `arg_left...`，这里是包的展开，就是将参数名字展开为逗号分割的参数列表。

在函数

我们无法像数组一样直接使用参数包中的参数，而需要对参数包进行解包。通常解包的方式有两种：

- 逐层实例化函数

```cpp
// 出口函数
void Unpack() { }
// 逐层解包
template<class Tp, class...Args>
void Unpack(Tp elem, Args... a)
{
    std::cout << elem << std::endl;
    Unpack(a...);
}

template<class... Args>
void f(Args... a)
{
    Unpack(a...);
}

int main()
{
    f("asd", 123, 1.1);
    return 0;
}
/*
输出结果：
asd
123
1.1
*/
```

`Unpack` 会生成若干个函数，每层函数都会比上一层的参数少一，最后显示实例化一个出口函数，当参数包的参数都被解析出来后就停止。

- 逗号表达式

```cpp
template<class Tp>
void print(Tp& a) { std::cout << a << std::endl; }

template<class... Args>
void f(Args... a)
{
    std::vector<int> vec{ (print(a),0)...};
}
int main()
{
    f("asd", 123, 1.1);
    return 0;
}
/*
输出结果：
asd
123
1.1
*/
```

此方法在构造数组 `vec`  的过程中就将 `a` 进行了展开。`{ (print(a),0)...}` 最后展开的结果就是 `(print(arg1),0),(print(arg2),0),(print(arg3),0),...etc `。

C++11 还提供了一个新的关键字来计算参数包的大小 `sizeof...()`：

```cpp
template<class... Args>
void f(Args... a)
{
    std::cout << sizeof...(a) << std::endl;
}

int main()
{
    f("asd", 123, 1.1);
    return 0;
}
/* 输出结果：3 */
```



## **SFINAE**

我们在代码中调用模板函数或使用模板类时，编译器在编译的时候会将所有同名的函数或类放入重载集中，再根据具体实参和形参的匹配情况，找到最符合条件的模板，这个选择的过程会按照以下优先级：

1. 形参实参完全匹配；
2. 实参只需进行简单的 `cv` 限定符转换；
3. 形参为可变模板参数。

我们在编写模板的时候，想要在调用时精确的匹配我们所期望的模板仅依靠上述优先级是不够的，这时就要用到**SFINAE（Substitution Failure Is Not An Error），替换失败不是错误。**

在 C++11 标准中它的定义是：在模板形参替换为具体实参后，导致类型或表达式不符合语法时，那么这属于替换失败，编译器不会进行语法报错，而是从重载集中丢弃这个模板。

我们看下面这个例子，在这个例子里我们希望 `IntOnly` 这个函数只接受整型类型：

```cpp
template<
    class Tp,
    class = std::enable_if<std::is_integral<Tp>::value>::type
>
void IntOnly(const Tp& a)
{
    std::cout << a << std::endl;
}

// 用来接收其他不符合条件的类型
template<class>
void IntOnly(...)
{
    std::cout << "This func need a int type" << std::endl;
}

class A{};
int main()
{
    IntOnly<int>(3);
    IntOnly<char>('a');
    IntOnly<long long>(4ll);
    IntOnly<double>(.2);
    IntOnly<A>(A());
    return 0;
}
/*
运行结果：
3
a
4
This func need a int type
This func need a int type
*/
```

这里我们用到了 `std::enable_if` 和 `std::is_integral` ，后者就是判断类型是否为整形类型，这里不展开说了。主要介绍 `std::enable_if`，它是 C++11 提供实现 SFINAE 的模板类，它定义如下：

```cpp
/// Define a member typedef @c type only if a boolean constant is true.
template<bool, typename _Tp = void>
struct enable_if
{ };

// Partial specialization for true.
template<typename _Tp>
struct enable_if<true, _Tp>
{ typedef _Tp type; };
```

它有两个模板参数，当第一个模板参数为 `ture` 时，它内部会提供 `_Tp` 的类型 `type`，`_Tp` 默认值为 `void`。如果第一个模板参数为 `false` ，则内部没有 `type`。我们分析一下上述的匹配过程：

- 当 `_Tp` 为整型时，表达式 `std::is_integral<Tp>::value` 为真时，匹配特化版本， `enable_if` 内部有 `type` 类型，语句合法，正确匹配到第一个 `IntOnly`。

- 当 `_Tp` 不是整形时，表达式 `std::is_integral<Tp>::value` 为假，`enable_if` 内部没有 `type` 类型，语句不合法，此时为替换失败，而不是编译错误，编译器会向下继续匹配更合适的模板，最后匹配到可变参数的 `IntOnly(...)`。

使用 SFINAE 的编程技巧，可以让我们进行更复杂的类型检查，如判断一个类型是否拥有某种成员函数或成员变量，这就需要用库中的其他类来实现。

## **type_traits**

下面介绍一些 `<type_traits>` 库中提供的工具。

### **构造类型引用**

C++11 提供了两个工具，方便我们构造一个类型的左值引用和右值引用：

```cpp

template< class T >
struct add_lvalue_reference;

template< class T >
struct add_rvalue_reference;
```

结构体中提供 type 为添加引用后的类型。对于一些不可引用类型，如 `void`，如果直接使用 `void&` 会报错，使用 `add_lvalue_reference<void>::type` 的类型是 `void`。

C++14 提供了两个重命名，方便使用：

```cpp
template< class T >
using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;
template< class T >
using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;
```

###  **`std::declval`**

```cpp
// Defined in header <utility>
template< class T >
typename std::add_rvalue_reference<T>::type declval() noexcept;
```

当我们想判断一个类型是否支持某种参数或含有某个属性时，可以使用该函数创建一个引用，调用对应的函数或访问对应的属性值，再使用 `decltype` 表达式判断类型是否为合法类型。

下面是一个判断一个类型是否具有 `+` 操作的例子：

```cpp
// 一个帮助类型，用于检测类型T是否支持加法运算符+
template <typename T, typename = void>
struct has_addition : std::false_type {};

// 专门化版本，当T类型支持加法运算时，
// std::void_t<decltype(std::declval<T>() + std::declval<T>())> 是有效的
template <typename T>
struct has_addition<
    T, 
    std::void_t<decltype(std::declval<T>() + std::declval<T>())>
    > : std::true_type {};
```

这里 `void_t` 是 C++17 提供的实现 `SFINAE` 的表达式，它的定义如下：

```cpp
template <class... _Types>
using void_t = void;
```

## **模板别名**

因为 `typedef` 无法重定义一个模板的别名，所以在 c++98 中想要给一个模板起别名需要套一个类来实现，如下：

```cpp
template<class Tp>
struct pi
{
    typedef std::pair<int, Tp> pair;
};
pi<int>::pair a;
```

这样可读性很低，而且编写时很麻烦。所以在 C++11 中，新增了一个特性就是可以通过使用using来为一个模板定义别名，如下:

```cpp
template<class Tp>
using pi = std::pair<int,Tp>;
```






