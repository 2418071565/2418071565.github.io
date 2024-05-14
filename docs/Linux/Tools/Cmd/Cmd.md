## **jobs/fg/bg**

查看当前用户启动的后台进程及其编号和状态。

我们可以运行可执行文件的指令后加上 `&` 来直接后台启动。

```cpp
[可执行程序] &
```

我们可以使用 `fg` 指令将一个后台进程变为前台进程。使用 `bg` 指令将一个进程变为后台进程。

我们可以使用 `ctrl + z` 将一个前台进程暂停挂起到后台。使用 `bg` 命令可以将暂停的进程重新运行。

```cpp
fg [任务编号]
bg [任务编号]
```

## **ipcs/ipcrm**

ipcs 显示 System V IPC 的各种设施：共享内存，消息队列，信号量组。
有以下选项：
```shell
-m, --shmems
    Write information about active shared memory segments.

-q, --queues
    Write information about active message queues.

-s, --semaphores
    Write information about active semaphore sets.

-a, --all
    Write information about all three resources (default).
```

ipcrm 删除 System V IPC 的各种设施。

```shell
-M, --shmem-key shmkey
    Remove the shared memory segment created with shmkey after the last detach is performed.

-m, --shmem-id shmid
    Remove the shared memory segment identified by shmid after the last detach is performed.

-Q, --queue-key msgkey
    Remove the message queue created with msgkey.

-q, --queue-id msgid
    Remove the message queue identified by msgid.

-S, --semaphore-key semkey
    Remove the semaphore created with semkey.

-s, --semaphore-id semid
    Remove the semaphore identified by semid.
```

## **scp/rcp**

借助 `ssh` 实现的文件传输工具。

```shell
scp [可选项] source target
```



## **zip/unzip**

语法： zip 压缩文件.zip 目录或文件。
功能： 将目录或文件压缩成zip格式。
常用选项：

`-r` 递归处理，将指定目录下的所有文件和子目录一并处理。

## **ldd**
 
`ldd` 显示可执行程序链接的动态库。

```shell
ldd [可执行程序]
```

## **ulimit**

`ulimit` 为 shell 内建指令，可用来控制 shell 执行程序的资源。

#### 选项

`-a`：显示所有资源限制。

`-c`：设置core文件的大小限制。

`-d`：设置数据段大小限制。

`-f`：设置文件大小限制。

`-m`：设置内存大小限制。

`-n`：设置打开文件数限制。

`-p`：设置缓冲区大小限制。

`-s`：设置栈大小限制。

`-t`：设置CPU时间限制。
