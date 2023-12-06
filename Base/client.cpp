#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <iostream>
#include <string.h>
void error_handling(const char *error);
int main(int argc, char *argv[])
{
    int server_sock;
    int client_sock;
    struct sockaddr_in server_addr
    {
        0
    }; // 声明两个地址
    struct sockaddr_in client_addr
    {
        0
    };                                //
    char message[] = "Hello, world!"; // 要发送的信息
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << std::endl;
        exit(1);
    }
    server_sock = socket(PF_INET, SOCK_STREAM, 0); // 返回文件描述符
    if (server_sock == -1)
    {
        error_handling("server套接字创建失败");
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(atoi(argv[0]));
    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
        error_handling("bind Error");
    if (listen(server_sock, 5) == -1)
        error_handling("listen Error");
    client_addr
}
void error_handling(const char *message)
{
    std::cerr << message << "\n";
}