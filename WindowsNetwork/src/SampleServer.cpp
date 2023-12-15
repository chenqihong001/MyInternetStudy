#include <iostream>
#include <WinSock2.h>
int main(int argc, char *argv[])
{
    WSADATA wsaData; // 创建Winsock库初始化信息体
    SOCKET clientSocket;
    SOCKET serverSocket;

    // 创建客户端，服务端套接字
    SOCKADDR_IN clientAddr{}; // 创建客户端，服务端网络地址结构体
    SOCKADDR_IN serverAddr{};
    int clientAddrSize = sizeof(clientAddr);
    WSAStartup(MAKEWORD(2, 2), &wsaData);                     // 初始化Winsock库
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // 初始化服务端套接字
    // 初始化server端网络地址结构体
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); // inaddr_any
    serverAddr.sin_port = htons(atoi(argv[1]));
    bind(serverSocket, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, 5); // 2.backlog
    clientSocket = accept(serverSocket, (SOCKADDR *)&serverAddr, &clientAddrSize);
    // 返回客户端套接字，并得到客户端结构体大小
    //...accept阻塞线程
    const char *message = "The Message is sended by Server";
    // 客户端与服务端通过套接字通信
    send(clientSocket, message, strlen(message) + 1, 0);
    closesocket(serverSocket);
    closesocket(clientSocket);
    WSACleanup();
    return 0;
}