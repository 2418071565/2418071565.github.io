
## **简介**

C++20 中引入了信号量，位于头文件 `<semaphore>` 中。

它提供了两种信号量：

- counting_semaphore：模板类，定义如下：

```cpp
template< std::ptrdiff_t LeastMaxValue = /* implementation-defined */ >
class counting_semaphore;
```
  
模板参数 `LeastMaxValue` 为信号量的的初始值，其默认值不同平台的实现不同。这里 ptrdiff_t 是一个有符号数，具体类型要看编译器具体是实现。

在 MSVC 下 `LeastMaxValue` 默认值为 `long long` 的最大值，在 gcc(11.2.0) 下该值是 `long int` 的最大值。

- binary_semaphore：它是一个两种状态的信号量，他的定义如下：

```cpp
using binary_semaphore = std::counting_semaphore<1>;
```

counting_semaphore 不支持默认构造，拷贝和移动语义。我们在创建信号量时要传给构造函数一个值，作为信号量计数器的初始状态：

```cpp
std::counting_semaphore<10> csem(1);// 初始计数器为 1
```

## **P/V 操作**

### **P 操作**

提供了三种 P 操作方式：

- `acquire`：阻塞式，直到申请到信号量。

- `try_acquire`：无阻塞式申请。
 
- `try_acquire_for`：阻塞式，申请信号量，但只阻塞一段时间。
 
- `try_acquire_until`：阻塞至某个时间点。

后两个关于时间的函数可以使用 `<chrono>` 给出。 还有一个 `max` 函数，他会返回内部计数器的最大可能值。

### **V 操作**

只有一个 `release` 函数，表示信号量计数器的值 +1。

