

## **用途**

decltype(auto) 可以用来声明变量以及指示函数返回类型。

当使用 decltype(auto) 来声明变量时，该变量应立即被初始化，


- **decltype(auto)**:


`decltype(auto)` 是一种简写，可以自动推导表达式的类型，同时保留表达式的所有特性（包括引用和 cv 限定符）。

```cpp
int x = 0;
int& foo() { return x; }
decltype(auto) y = foo();  // y 是 int&，保持了 foo() 的返回类型
```

- **与 `decltype` 一起使用的返回类型后置语法**：


可以在函数定义中使用 `decltype` 推导返回类型。

```cpp
auto add(int a, int b) -> decltype(a + b) {
    return a + b;
}
```


