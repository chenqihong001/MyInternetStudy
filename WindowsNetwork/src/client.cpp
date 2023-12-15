#include <iostream>
#include <WinSock2.h>
#include <string.h>
// 1.int WSAStartUp(WORD wVersionRequest,LPWSADATA lpWSAData)
// 2.int WSACleanup() 成功返回0,失败返回SOCKET_ERROR
// 3.SOCKET socket(int af,int type,int protocol);成功时返回套接字句柄，失败返回INVALID_SOCKET
// 4.int bind(SOCKET s,const struct sockaddr* name,int namelen);返回0,SOCKET_ERROR
// 5.int listen(SOCKET s,int backlog);0,SOCKET_ERROR
// 6.SOCKET accept(SOCKET s,struct sockaddr* addr,int *addrlen);
// 7.int connect(SOCKET s,const struct sockaddr* name,int namelen);
// 8.int closesocket(SOCKET s);
// Windows区分《文件句柄》和《套接字句柄》
void ErrorHandling(const char *message);
int main(int argc, char *argv[])
{

    WSADATA WSAData;      // 该结构体用于存储初始化Winsock库后的信息
    SOCKET hSocket;       // handle
    SOCKADDR_IN servAddr; // 创建服务端网络地址结构体
    char message[1024];
    int strLen;
    if (argc != 3)
    {
        printf("main参数不对 file:%s", argv[0]);
        exit(1);
    }

    if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0) // 成功返回0，MAKEWORD->Winsock库的版本2.2
    {
        ErrorHandling("WSAStartup()Error");
    }
    // 初始化Winsock库
    hSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); // 初始化socket
    if (hSocket == INVALID_SOCKET)
        ErrorHandling("socket()Error");
    memset(&servAddr, 0, sizeof(servAddr)); // 初始化网络地址结构体内的数据

    servAddr.sin_family = AF_INET;                 // ipv4协议族
    servAddr.sin_addr.s_addr = inet_addr(argv[1]); // ipv4字符串形式转为网络字节序
    servAddr.sin_port = htons(atoi(argv[2]));
    if (connect(hSocket, (SOCKADDR *)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
        ErrorHandling("connect()Error");
    // 一旦连接成功，客户端就和服务端的套接字建立联系
    strLen = recv(hSocket, message, sizeof(message) - 1, 0); // 留出一位用于存储\0
    if (strLen == -1)
        ErrorHandling("rece()Error");
    message[strLen] = '\0';
    printf("Received Message is :%s", message);
    closesocket(hSocket);
    WSACleanup(); // 清理Winsock库
    // 返回受到的字节数，关闭返回0，失败返回SOCKET_ERROR
    return 0;
}
void ErrorHandling(const char *message)
{
    std::cout << message;
    exit(1);
}