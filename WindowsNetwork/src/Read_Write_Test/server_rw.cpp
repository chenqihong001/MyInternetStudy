#include <WinSock2.h>
#include <iostream>
#include <codecvt>
#include <locale>
int main(int argc, char *argv[])
{

    SOCKET serv_sock{};
    SOCKET clnt_sock{};
    SOCKADDR_IN servAddr{};
    SOCKADDR_IN clntAddr{};
    int clntAddrSize = sizeof(clntAddr);
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(atoi(argv[1]));
    bind(serv_sock, (SOCKADDR *)&servAddr, sizeof(servAddr));
    listen(serv_sock, 5);
    std::cout << "断点0" << std::endl;
    clnt_sock = accept(serv_sock, (SOCKADDR *)&servAddr, &clntAddrSize); // 返回客户端套接字
    // 信息交流开始
    char recv_buffer[1024]{};
    std::string send_message = "Chinese You Are";
    const char *mess = "Great Boy";
    // send(clnt_sock, send_message.c_str(), send_message.length(), 0); // 先发送，后接收
    // send(clnt_sock, mess, 64, 0);                                    // 先发送，后接收
    std::cout << "断点1" << std::endl;
    int length = recv(clnt_sock, recv_buffer, 1024, 0);
    std::cout << "断点2" << std::endl;
    recv_buffer[length] = '\0';
    std::cout << "服务端收到的信息：" << recv_buffer << std::endl;
    closesocket(clnt_sock);
    closesocket(serv_sock);
    WSACleanup();
    return 0;
}