
**详细查看 man 手册，这里将接口列出。**

## **设置/获取资源限制**

```cpp
#include <sys/time.h>
#include <sys/resource.h>

int getrlimit(int resource, struct rlimit *rlim);
int setrlimit(int resource, const struct rlimit *rlim);
```

[linux下getrlimit()与setrlimit()函数说明及使用](https://blog.csdn.net/wgl307293845/article/details/106897131/){target="_blank"}