
**详细查看 man 手册，这里将接口列出。**


## **关闭 Socket 的读端或写端**


```c
#include <sys/socket.h>
int shutdown(int sockfd, int how);
```

shutdown（）调用会关闭与 sockfd 关联的套接字上的全部或部分全双工连接。如果 how 是 SHUT_ RD，就关闭 socket 的读端。如果how 是 SHUT_WR，就关闭写端。如果 how 是 SHUT_RDWR ，读写都被关闭，类似 `close()`。

## **删除文件**

删除指定文件

```c
#include<unistd.h>
int unlink(const char* pathname);
```

## **设置/获取资源限制**

```cpp
#include <sys/time.h>
#include <sys/resource.h>

int getrlimit(int resource, struct rlimit *rlim);
int setrlimit(int resource, const struct rlimit *rlim);
```

[linux下getrlimit()与setrlimit()函数说明及使用](https://blog.csdn.net/wgl307293845/article/details/106897131/){target="_blank"}


## **c 语言执行命令接口**

通过管道在两个进程间传递消息。

```cpp
#include <stdio.h>

FILE *popen(const char *command, const char *type);

int pclose(FILE *stream);
```

该接口将 fork 一个子进程执行命令 `command` ，如果 `type` 是 "r"，被调用程序的输出就可以被调用程序使用，调用程序利用popen函数返回的FILE＊文件流指针。如果 `type` 是 "w"，调用程序就可以用 `fwrite` 调用向被调用程序发送数据，而被调用程序可以在自己的标准输入上读取这些数据。
