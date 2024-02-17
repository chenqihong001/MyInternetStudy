#include <iostream>
#include <sys/socket.h>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
const int BUF_SIZE = 40;
// 创建缓冲区
char buf[BUF_SIZE]{};

// 创建套接字
int acpt_sock; // 服务端
int recv_sock; // 客户端
int main()
{
    // struct sockaddr_in recv_addr,send_addr
    // struct sigaction信号系统
    acpt_sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in acpt_addr;
    memset(&acpt_addr, 0, sizeof(acpt_addr));

    // 初始化recv地址
    acpt_addr.sin_family = AF_INET;
    acpt_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    std::cout << "请输入端口号(port):";
    std::string port;
    std::cin >> port;
    acpt_addr.sin_port = htons(atoi(port.c_str()));

    // 为套接字绑定地址，初始化套接字
    if (bind(acpt_sock, (struct sockaddr *)&acpt_addr, sizeof(acpt_addr)) == -1)
        std::cerr << "Error bind()\n";
    listen(acpt_sock, 16);
    struct sockaddr_in clnt_addr;
    socklen_t clntAddrSize = 0;
    recv_sock = accept(acpt_sock, (struct sockaddr *)&clnt_addr, &clntAddrSize);
}