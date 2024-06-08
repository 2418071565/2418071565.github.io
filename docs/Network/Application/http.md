

## **简介**

HTTP 是超文本传输协议，也就是HyperText Transfer Protocol。HTTP 是一种无状态的基于 TCP/IP 的用户层传输协议。



## **内容**


### **Header**


HTTP 报文的头部是一系列的 Key-Value 的键值对，如下就是一个 HTTP 协议的报文：

```
GET / HTTP/1.1
Host: 127.0.0.1:8888
Connection: keep-alive
Cache-Control: max-age=0
sec-ch-ua: "Google Chrome";v="125", "Chromium";v="125", "Not.A/Brand";v="24"
sec-ch-ua-mobile: ?0
sec-ch-ua-platform: "Windows"
Upgrade-Insecure-Requests: 1
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/125.0.0.0 Safari/537.36
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7
Sec-Fetch-Site: cross-site
Sec-Fetch-Mode: navigate
Sec-Fetch-User: ?1
Sec-Fetch-Dest: document
Accept-Encoding: gzip, deflate, br, zstd
Accept-Language: zh-CN,zh;q=0.9
```

- **第一行：**标识了 HTTP 请求的类型，有 GET，POST，PUT，DELETE 等。还有 HTTP 协议的版本，有 1.0，1.1，2，3 等。

GET：向特定的资源发出请求。

POST：向指定资源提交数据进行处理请求（例如提交表单或者上传文件）。数据被包含在请求体中。POST请求可能会导致新的资源的创建和/或已有资源的修改。

PUT：向指定资源位置上传其最新内容。 

DELETE：请求服务器删除Request-URI所标识的资源。 




### **Body**

