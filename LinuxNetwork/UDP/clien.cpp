#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <cstring>
const int BUFFER_SIZE = 1024;
int main(int argc, char *argv[])
{
    // socker
    // init sockadrr_in
    // sento如果没有为socket分配ip,port,第一次调用此函数时，自动分配,ip为本机ip,port随机分配一个空port
    // recvfrom
    // close
    int clntSocket = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    std::cout << "请输入端口号：";
    std::string port;
    std::cin >> port;
    addr.sin_port = htons(atoi(port.c_str()));
    std::string message;
    char buffer[BUFFER_SIZE]{};
    int buf_int{};
    socklen_t len = sizeof(buffer);
    ssize_t recv_len{};
    int sum{};
    for (int i = 0; i < 100000; i++)
    {
        // std::cout << "请输入：";
        // std::cin >> message;
        sendto(clntSocket, &i, sizeof(int), 0, (struct sockaddr *)&addr, sizeof(addr));
        // 在每次接收信息之前清空 buffer
        memset(&buf_int, 0, sizeof(buf_int));
        recv_len = recvfrom(clntSocket, &buf_int, sizeof(int), 0, (struct sockaddr *)&addr, &len);
        sum++;
        std::cout << "返回的值：" << buf_int << std::endl;
    }
    std::cout << "The Sum :" << sum << std::endl;
    shutdown(clntSocket, SHUT_WR);
    close(clntSocket);
    return 0;
}
