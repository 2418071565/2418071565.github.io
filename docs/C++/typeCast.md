

标准C++为了加强类型转换的可视性，引入了四种命名的强制类型转换操作符：`static_cast`、`reinterpret_cast`、`const_cast`、`dynamic_cast`。


## **`static_cast`**

`static_cast` 用于非多态类型的转换（静态转换），编译器隐式执行的任何类型转换都可用 `static_cast` ，但它不能用于两个不相关的类型进行转换。

```cpp
int main()
{
    double d = 12.34;
    int a = static_cast<int>(d);
    cout<<a<<endl;
    return 0;
}
```


## **`reinterpret_cast`**


`reinterpret_cast` 操作符通常为操作数的位模式提供较低层次的重新解释，用于将一种类型转换为另一种不同的类型，但也要有一定关联，如：改变指针或引用的类型、将指针或引用转换为一个足够长度的整形、将整型转换为指针或引用类型。

```cpp
int main()
{
    // 这里使用static_cast会报错，应该使用reinterpret_cast
    //int *p = static_cast<int*>(a);
    int *p = reinterpret_cast<int*>(a);
    return 0;
}
```


## **`const_cast`**

`const_cast` 最常用的用途就是删除变量的 `const` 属性，方便赋值，要注意的是 `const_cast` 只能转换指针引用的类型。


```cpp
void Test ()
{
    const int a = 2;
    int* p = const_cast<int*>(&a);
    *p = 3;
    cout<< a <<endl;
    return 0;
}
```

??? warning "一些编译器优化"
    被 `const` 修饰的类型，编译器会认为该值不会变，可能会把他当作宏替换掉代码中的变量，或者只使用寄存器中的值。

    ```cpp
    int main() {   
        const int a = 2;
        int* p = const_cast<int*>(&a);
        *p = 3;
        std::cout << a << std::endl;
        // 00007FF68B795A06  mov         edx,2 
        // 这里 VS2022 C++14标准的编译器直接将 a 替换为了 2
        std::cout << *p << std::endl;
        return 0;
    }
    ```

    所以这个输出的值为 2 和 3，要避免这样的优化就要加上 `volatile` 关键字，每次取值都要到内存中。


## **`dynamic_cast`**


`dynamic_cast` 用于将一个父类对象的指针/引用转换为子类对象的指针或引用(动态转换)

- 向上转型：子类对象指针/引用->父类指针/引用(不需要转换，赋值兼容规则)

- 向下转型：父类对象指针/引用->子类指针/引用(用 `dynamic_cast` 转型是安全的)

当转换失败返回 `nullptr`，可以识别当前父类指针指向的位置是否为子类对象。

注意：

1. `dynamic_cast` 只能用于父类含有虚函数的类；

2. `dynamic_cast` 会先检查是否能转换成功，能成功则转换，不能则返回 0。