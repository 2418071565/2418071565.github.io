

## **基础概念**



### **网络字节序**

我们都知道不同机器上的字节序可以分为两种：大端机、小端机。在网络通信时，数据传入到不同字节序的机器必然会导致，数据的错乱，所以在网络数据传递时，要求必须是按大端字节序传递数据。系统为我们提供了转网络字节序的方法：


```cpp
#include <arpa/inet.h>

// host to net
uint32_t htonl(uint32_t hostlong);
uint16_t htons(uint16_t hostshort);

// net to host
uint32_t ntohl(uint32_t netlong);
uint16_t ntohs(uint16_t netshort);
```

## **常用接口**


```cpp
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
in_addr_t inet_addr(const char *cp);    // 点分十进制转 4 字节网络字节序的 ip
char *inet_ntoa(struct in_addr in);     // 4 字节网络字节序的 ip 转点分十进制字符串


#include <arpa/inet.h>
// 点分十进制的 IPv4 或 IPv6 的地址 -> 4 字节网络字节序的 ip
int inet_pton(int af, const char *src, void *dst);  

//  4 字节网络字节序的 ip -> 点分十进制的 IPv4 或 IPv6 的地址
const char *inet_ntop(int af, const void *src,
                        char *dst, socklen_t size);

```

