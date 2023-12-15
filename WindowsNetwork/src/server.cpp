#include <iostream>
#include <WinSock2.h>
#include <string.h>
void ErrorHandling(const char *message);
int main(int argc, char *argv[]) // 字符串数组
{
    WSADATA WSAData;                    // 关于版本信息的结构体
    SOCKET hServSock, hClntSock;        // SOCKET->unsigned _int64
    SOCKADDR_IN servAddr{}, clntAddr{}; // 两个地址，SOCKETADDR_IN->(sin_family,sin_port,sin_addr,sin_zero[8])
    // 网络地址结构体
    //{}使用聚合初始化
    int szClntAddr;
    const char *message = "I am the best boy";
    if (argc != 2)
    {
        printf("Useage :%s <port>\n", argv[0]);
        exit(1);
    }
    if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0) // 成功返回0
    {
        ErrorHandling("WSASatrtup() error");
    }
    hServSock = socket(PF_INET, SOCK_STREAM, 0); // 失败返回INVALID_SOCKET
    if (hServSock == INVALID_SOCKET)
    {
        ErrorHandling("server socket() error");
    }
    // memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY); // host to network long
    // htonl用于将32位整数由主机字节序转换为网络字节序（大端序）
    // 表示监听的对象的地址
    servAddr.sin_port = htons(std::stoi(argv[1])); // host to network short,  ASCII to integer
    if (bind(hServSock, (SOCKADDR *)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
        ErrorHandling("bind()Error");
    if (listen(hServSock, 5) == SOCKET_ERROR) // (第二个参数)backlog 表示允许在套接字队列中等待连接的最大数量
        ErrorHandling("listen()Error");
    // listen设置套接字为监听状态
    szClntAddr = sizeof(clntAddr);                                     // 客户端网络地址结构体
    hClntSock = accept(hServSock, (SOCKADDR *)&servAddr, &szClntAddr); // 客户端网络地址结构体的大小
    // accept返回一个套接字
    //  accrpt会阻塞程序
    // 第三个参数，在函数调用后会被修改为实际的地址结构大小
    if (hClntSock == INVALID_SOCKET)
        ErrorHandling("accept()Error");
    send(hClntSock, message, sizeof(message), 0);
    // send用于server向客户端发送信息
    closesocket(hClntSock);
    closesocket(hServSock);
    WSACleanup();
    return 0;
}

void ErrorHandling(const char *message)
{
    std::cout << message;
    exit(1);
}