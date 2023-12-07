#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
void error_handling(const char *message);

int main(int argc, char *argv[])
{
    int sock;
    struct sockaddr_in serv_addr; // 以sockaddr_in 声明服务端地址(ip,port)，后面强制转为sockaddr
    char message[30];
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

    str_len = read(sock, message, sizeof(message) - 1);
    if (str_len == -1)
    {
        error_handling("read() error!");
    }

    printf("Message from server : %s\n", message);
    close(sock);
    return 0;
}

void error_handling(const char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}