#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <iostream>
void error_handling(const char *message);
typedef struct sockaddr_in SOCKADDR_IN;
int main(int argc, char *argv[])
{
    int sock;
    SOCKADDR_IN serv_addr; // 以sockaddr_in 声明服务端地址(ip,port)，后面强制转为sockaddr

    int str_len;
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // 客户端，inet_addr(ip地址)把字符串的ip地址转化为2进制;
    // inet_aton(argv[1], &serv_addr.sin_addr);
    serv_addr.sin_port = htons(atoi("9999")); // host to internet short 将字节序整数转为网络字节序
    // atoi->ASCII to Integer
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("connect() error!");
    char message[30];
    char mess[30];
    str_len = read(sock, message, 9);
}
void error_handling(const char *message)
{
    std::cout << message << std::endl;
}