

## **简介**

HTTP 是超文本传输协议，也就是HyperText Transfer Protocol。HTTP 是一种无状态的基于 TCP/IP 的用户层传输协议。



## **内容**


### **Header**


HTTP 报文的头部是一系列的 Key-Value 的键值对，如下就是一个 HTTP 请求报文头部：

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

<<<<<<< HEAD
<<<<<<< HEAD
- **第一行：**标识了 HTTP 请求的类型，有 GET，POST，PUT，DELETE 等。还有 HTTP 协议的版本，有 1.0，1.1，2，3 等。
=======
=======
>>>>>>> 06757e4 (Update:HTTP)

#### **请求头/响应头**

如果是请求头，会标识 HTTP 请求的类型，有 GET，POST，PUT，DELETE 等。请求头会有访问的资源路径，这里是 `\`。还有 HTTP 协议的版本，有 1.0、1.1、2、3 等。

- 请求类型：
<<<<<<< HEAD
>>>>>>> master
=======
>>>>>>> 06757e4 (Update:HTTP)

GET：向特定的资源发出请求。

POST：向指定资源提交数据进行处理请求（例如提交表单或者上传文件）。数据被包含在请求体中。POST请求可能会导致新的资源的创建和/或已有资源的修改。

PUT：向指定资源位置上传其最新内容。 

<<<<<<< HEAD
<<<<<<< HEAD
DELETE：请求服务器删除Request-URI所标识的资源。 
=======
DELETE：请求服务器删除Request-URI所标识的资源。

如果是响应头，会指名 HTTP 协议版本和状态码。

- 状态码：

状态码分为 5 类信息响应(100–199)，成功响应(200–299)，重定向(300–399)，客户端错误(400–499)和服务器错误 (500–599)。
>>>>>>> 06757e4 (Update:HTTP)


#### **Host**

客户端发送请求时，用来指定服务器的域名。

#### **Connection**

和服务器的连接方式，有长连接和短连接。HTTP 长连接的特点是，只要任意一端没有明确提出断开连接，则保持 TCP 连接状态，便于其他请求复用。而短连接是在接收完数据后，就断开 TCP 连接。


#### **数据相关**

- **Accept**：请求头内容，声明自己可以接受哪些数据格式。

- **Content-Type**：响应头的内容，标识返回的数据类型，还有编码方式，如： `text/html; Charset=utf-8`。

- **Accept-Encoding**：请求头内容，说明自己可以接受哪些压缩方法。

- **Content-Encoding**：响应头的内容，说明数据的压缩方法。表示服务器返回的数据使用了什么压缩格式。如：gzip。


- **Content-Length**：响应头内容，标识数据长度。HTTP 协议通过设置回车符、换行符作为 HTTP header 的边界，通过 Content-Length 字段作为 HTTP body 的边界，这两个方式都是为了解决“粘包”的问题。

其他头部，后文再详细介绍。

### **Body**

<<<<<<< HEAD
=======
DELETE：请求服务器删除Request-URI所标识的资源。

如果是响应头，会指名 HTTP 协议版本和状态码。

- 状态码：

状态码分为 5 类信息响应(100–199)，成功响应(200–299)，重定向(300–399)，客户端错误(400–499)和服务器错误 (500–599)。


#### **Host**

客户端发送请求时，用来指定服务器的域名。

#### **Connection**

和服务器的连接方式，有长连接和短连接。HTTP 长连接的特点是，只要任意一端没有明确提出断开连接，则保持 TCP 连接状态，便于其他请求复用。而短连接是在接收完数据后，就断开 TCP 连接。


#### **数据相关**

- **Accept**：请求头内容，声明自己可以接受哪些数据格式。

- **Content-Type**：响应头的内容，标识返回的数据类型，还有编码方式，如： `text/html; Charset=utf-8`。

- **Accept-Encoding**：请求头内容，说明自己可以接受哪些压缩方法。

- **Content-Encoding**：响应头的内容，说明数据的压缩方法。表示服务器返回的数据使用了什么压缩格式。如：gzip。


- **Content-Length**：响应头内容，标识数据长度。HTTP 协议通过设置回车符、换行符作为 HTTP header 的边界，通过 Content-Length 字段作为 HTTP body 的边界，这两个方式都是为了解决“粘包”的问题。

其他头部，后文再详细介绍。

### **Body**

=======
>>>>>>> 06757e4 (Update:HTTP)
请求数据也叫主体，可以添加任意的其他数据。数据大小等于头部中的 `Content-Length` 。


## **缓存**


<<<<<<< HEAD
>>>>>>> master
=======
>>>>>>> 06757e4 (Update:HTTP)
