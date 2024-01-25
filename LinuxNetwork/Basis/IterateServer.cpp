#include <iostream>
#include <sys/socket.h>
#include <unistd.h>    //read/write
#include <arpa/inet.h> //网络地址结构体
const int BUF_SIZE = 1024;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
inline void Error_handling(const char *str)
{
    std::cout << str << std::endl;
    exit(1);
}
int main(int argc, char *argv[])
{
    int serv_sock{};
    int clnt_sock{};
    char messageBuffer[BUF_SIZE];
    SOCKADDR_IN servAddr{}; // 保证填充数组内部数据为0
    SOCKADDR_IN clntAddr{}; // 填充数组为unsigned char 类型，常用来表示字节
    if (argc != 2)
    {
        Error_handling("main函数参数不够");
        exit(1);
    }
    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
        Error_handling("socket()Error");
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(atoi(argv[1]));
    if (bind(serv_sock, (SOCKADDR *)&servAddr, sizeof(servAddr)) == -1)
        Error_handling("bind()Error");
    if (listen(serv_sock, 5) == -1)
        Error_handling("listen()Error");
    // 初始化客户端地址大小；
    socklen_t clntAddrSize = sizeof(clntAddr);
    for (int i = 0; i < 5; i++)
    {
        clnt_sock = accept(serv_sock, (SOCKADDR *)&servAddr, &clntAddrSize);
        if (clnt_sock == -1)
            Error_handling("accept()Error");
        else
            std::cout << "Connect client " << i + 1 << std::endl;
        int mess_len{};
        // while ((mess_len = read(clnt_sock, messageBuffer, BUF_SIZE)) != 0)
        // {
        //     write(clnt_sock, messageBuffer, mess_len); // 回声服务器
        // }
        close(clnt_sock); // 关闭返回的客户端套接字
    }
    close(serv_sock);
    return 0;
}