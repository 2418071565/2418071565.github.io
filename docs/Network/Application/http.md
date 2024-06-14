

## **简介**

HTTP 是超文本传输协议，也就是HyperText Transfer Protocol。HTTP 是一种无状态无连接的基于 TCP/IP 的用户层传输协议。

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

- **第一行：**标识了 HTTP 请求的类型，有 GET，POST，PUT，DELETE 等。还有 HTTP 协议的版本，有 1.0，1.1，2，3 等。

#### **请求头/响应头**

如果是请求头，会标识 HTTP 请求的类型，有 GET，POST，PUT，DELETE 等，会有访问的资源路径，这里是 `\`。还有 HTTP 协议的版本，有 1.0、1.1、2、3 等。

- 请求类型：

GET：向特定的资源发出请求。

POST：向指定资源提交数据进行处理请求（例如提交表单或者上传文件）。数据被包含在请求体中。POST请求可能会导致新的资源的创建和/或已有资源的修改。

PUT：向指定资源位置上传其最新内容。 


DELETE：请求服务器删除Request-URI所标识的资源。 

如果是响应头，会指名 HTTP 协议版本和状态码。

- 状态码：

状态码是服务器对我们该次请求处理的结果状态，状态码分为 5 类：

|状态码|类别|原因|
|:-:|:-:|:-:|
1xx|信息响应|接收的请求正在处理|
2xx|成功响应|请求正常处理完毕|
3xx|重定向|需要进行附加操作以完成请求|
4xx|客户端错误|服务器无法处理请求|
5xx|服务器错误|服务器处理请求出错|

最常见的状态码, 比如 200(OK), 404(Not Found), 403(Forbidden), 302(Redirect, 重定向), 504(Bad Gateway)。

这里的状态码，和 HTTP 的无状态无关。HTTP 的无状态意味着每个请求都是独立的，与之前的请求没有任何关联，服务器不会保留任何客户端请求的状态信息，这也就是说我们重复的向服务器申请同一资源时，服务器并不会识别出，我们曾多次申请过该数据。

但是浏览器可以能会对历史资源进行缓存，对针对缓存过的资源，并不会真的向服务器发送请求。

有一点对不上的是，我们在一个网站第一次登录之后，后续访问网站就不需要再次登录，这是因为使用了 Cookie，在后文介绍。



#### **Host**

客户端发送请求时，用来指定服务器的域名。

#### **Connection**

和服务器的连接方式，有长连接和短连接。HTTP 长连接的特点是，只要任意一端没有明确提出断开连接，则保持 TCP 连接状态，便于其他请求复用。而短连接是在接收完数据后，就断开 TCP 连接。

这里的连接，也和 HTTP 的无连接无关，HTTP 的无连接是每个请求/响应对在完成之后，客户端与服务器之间的连接就会关闭。每次请求时都需要重新建立连接，这样的做法使得服务器无需维持大量持久连接，减少了服务器资源的消耗。

#### **Location**

搭配3xx状态码使用, 告诉客户端接下来要去哪里访问。

#### **User-Agent**

声明用户的操作系统和浏览器版本信息。

#### **Cookie**

用于在客户端存储少量信息. 通常用于实现会话 (session) 的功能。

一般是当我们第一次登录一个网站时，服务器的响应 HTTP 报文中汇包含一个 `set-cookie` 字段，来让本地浏览器缓存一些用户信息，如密码，用户名等，当下次用户再次向该网站发送请求时，浏览器会自动将之前缓存的用户信息加到 HTTP 报文的 `cookie` 字段，来交给服务器进行验证，就可以避免用户多次重复的输入信息，以优化用户体验。

但是这个过程中有一个问题，就是服务器在进行 `set-cookie` 的响应中，用户信息是直接写在 HTTP 报文中的，这样的做法是很不安全的，用户的信息极易被盗取，这里就要提到 session，这时另一种记录客户状态的机制，不过 session 的用户信息被保存在服务器中，并且给每一个用户的信息分配一个独一无二 session ID 来标识每个用户，在服务器的响应 HTTP 报文中，也要进行 `set-cookie` ，不过这里让浏览器缓存的是 session ID，之后客户端再次访问时只需要将 session ID 交给服务器，即可辨别出用户。

但是这还没解决问题，只要抓包捕获到 session ID，就可以冒充用户。


#### **数据相关**

- **Accept**：请求头内容，声明自己可以接受哪些数据格式。

- **Content-Type**：响应头的内容，标识返回的数据类型，还有编码方式，如： `text/html; Charset=utf-8`。

- **Accept-Encoding**：请求头内容，说明自己可以接受哪些压缩方法。

- **Content-Encoding**：响应头的内容，说明数据的压缩方法。表示服务器返回的数据使用了什么压缩格式。如：gzip。

- **Content-Length**：响应头内容，标识数据长度。HTTP 协议通过设置回车符、换行符作为 HTTP header 的边界，通过 Content-Length 字段作为 HTTP body 的边界，这两个方式都是为了解决“粘包”的问题。



其他头部，后文再详细介绍。



### **Body**

要传输的内容，可以没有，长度不限。


### **GET 和 POST 的区别**

RFC 规定中 HTTP 协议中的安全是指请求方法不会修改服务器上的资源。

还有幂等的概念：多次执行相同的操作，结果都是相同的。

如果从 RFC 规范定义的语义来看：

GET 方法就是**安全且幂等的**，因为它是「只读」操作，无论操作多少次，服务器上的数据都是安全的，且每次的结果都是相同的。

POST 方法是 **不安全且不幂等的** ，因为是新增或提交数据的操作，会修改服务器上的资源，所以是不安全的，且多次提交数据就会创建多个资源，所以不是幂等的。

但实际开发中，并不一定会遵循上述规范，具体的情况要看具体的实现。

在 RFC 的规范中并没有规定 GET 方法不能有请求体，而且 URL 中的查询参数并不是只能出现在 GET 请求中，POST 请求也可以。

## 

## **缓存**


