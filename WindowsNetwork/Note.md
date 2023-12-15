# 网络编程（Windows端）

## 步骤

> 1. 网络环境初始化：WSAStartup
> 2. 创建服务器套接字：socket
> 3. 绑定本机IP和端口：bind
> 4. 监听客户端：listen
> 5. 等待客户端连接：accept
> 6. 发送消息：send
> 7. 接收消息：recv
> 8. 关闭socket：closesocket
> 9. 清除网络环境：WSACleanup

## 常用函数

1. `int WSAStartUp(WORD wVersionRequest,LPWSADATA lpWSAData)`
2. `int WSACleanup() 成功返回0,失败返回SOCKET_ERROR`
3. `SOCKET socket(int af,int type,int protocol);成功时返回套接字句柄，失败返回INVALID_SOCKET`
4. `int bind(SOCKET s,const struct sockaddr*name,int namelen);返回0,SOCKET_ERROR`
5. `int listen(SOCKET s,int backlog);0,SOCKET_ERROR`
6. `SOCKET accept(SOCKET s,struct sockaddr*addr,int*addrlen);`
7. `int connect(SOCKET s,const struct sockaddr* name,int namelen);`
8. `int closesocket(SOCKET s);`
Windows区分《文件句柄》和《套接字句柄》

## Server

1. WSADATA结构体（含有Winsock初始化信息）
2. Winsock初始化,WSAStartup(版本号，信息对象地址);
3. 初始化网络结构体地址Sin_addr
4. bind(),绑定套接字句柄和网络结构体地址
5. listen(servSocket,MAXSize);->listen设置套接字为监听状态
6. accept阻塞等待，返回连接的client套接字
7. send利用得到的client端的套接字进行通信

## Client

1. WSAStartup()初始化
2. 创建socket套接字
z
> `利用套接字在服务器与客户端之间进行信息通讯`
