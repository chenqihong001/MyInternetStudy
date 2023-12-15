#include <iostream>
#include <sys/socket.h>
// int socket(int family, int type, int protocol)
// type数据传输类型
// 套接字类型：
// 1.面向连接的套接字(SOCK_STREAM)
/*
特点：
    1.无损
    2.有序
    3.传输数据不存在数据边界
    4.套接字一一对应
*/
// 2.面向消息的套接字(SOCK_DGRAM) Datagram数据报
/*
特点：
    1.不可靠
    2.无序
    3.高速
    4.有数据边界->意味着接收数据的次数应和发送数据的次数相同
*/
int main(int argc, char *argv[])
{
    int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    int udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    return 0;
}