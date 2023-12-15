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

    if (argc != 3)
    {
        printf("usage: %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]); // 客户端，inet_addr(ip地址)把字符串的ip地址转化为2进制;
    serv_addr.sin_port = htons(atoi(argv[2]));      // host to internet short 将字节序整数转为网络字节序
    // atoi->ASCII to Integer
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("connect() error!");
    char message[30];
    char mess[30];
    str_len = read(sock, message, 9);
    int messLength = read(sock, mess, 10);
    // 多次调用read函数->不同于server端的write次数->体现了传输数据不存在边界性
    if (str_len == -1)
    {
        error_handling("read() error!");
    }
    message[str_len] = '\0';
    mess[messLength] = '\0';
    std::cout << message << std::endl;
    std::cout << mess << std::endl;
    close(sock);
    return 0;
}

void error_handling(const char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}