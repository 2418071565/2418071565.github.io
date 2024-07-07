

Linux 为实现多路复用提供了三个系统调用 select、poll 和 epoll，下面一一介绍。

## **select**

`select` 函数是 UNIX 系统中用于实现多路复用 I/O 操作的一个系统调用。它允许程序同时监控多个文件描述符（包括套接字、文件、管道等），从而在任何一个或多个文件描述符准备好进行 I/O 操作时得到通知。

`select` 会


以下是 `select` 函数的详细介绍：

### 函数原型

```c
#include <sys/select.h>

int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
```

### 参数说明

- **nfds**:整数值，是所有文件描述符的范围，即最大文件描述符加 1。通常可以通过 `FD_SETSIZE` 获取。
   
- **readfds**:指向 `fd_set` 结构的指针，表示需要监视是否有数据可读的文件描述符集合。如果不需要监视任何读事件，可以传递 NULL。
   
- **writefds**:指向 `fd_set` 结构的指针，表示需要监视是否可以写入数据的文件描述符集合。如果不需要监视任何写事件，可以传递 NULL。
   
- **exceptfds**:指向 `fd_set` 结构的指针，表示需要监视异常条件（如带外数据）的文件描述符集合。如果不需要监视任何异常事件，可以传递 NULL。
   
- **timeout**:指向 `timeval` 结构的指针，用于指定 `select` 的超时时间。可以为 NULL 表示无限期等待。`timeval` 结构定义了秒和微秒级别的超时值。

### 返回值

- 成功时返回准备好的文件描述符的数量。

- 超时返回 0。

- 失败时返回 -1，并设置 `errno`。

### **`fd_set` 操作**

`fd_set` 是一个集合，用于存储多个文件描述符。以下是操作 `fd_set` 的一些宏：

- **FD_ZERO(fd_set *set)**: 清空 `fd_set` 集合。

- **FD_SET(int fd, fd_set *set)**: 将文件描述符 `fd` 加入 `fd_set` 集合。

- **FD_CLR(int fd, fd_set *set)**: 从 `fd_set` 集合中移除文件描述符 `fd`。

- **FD_ISSET(int fd, fd_set *set)**: 检查文件描述符 `fd` 是否在 `fd_set` 集合中。

