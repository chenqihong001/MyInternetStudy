// 即使关闭套接字也会继续传输“输出”缓冲中的数据
// 关闭socket会丢失“输入”缓冲中的数据

// TCP滑动窗口协议
#include <iostream>
#include <thread>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
const int BUFFERSIZE = 1024;
using SOCKADDR = struct sockaddr;
using SOCKADDR_IN = struct sockaddr_in;
void ReadFunc(int _clntSocket, char *_buffer, int bufferSize)
{
    ssize_t num{};
    while (true)
    {
        num = read(_clntSocket, _buffer, bufferSize);
        if (num <= 0)
        {
            std::cout << "断开连接!!!\n";
            break;
        }
        std::cout << "来自客户端：" << _buffer << std::endl;
        // std::cout << "Read函数调用" << std::endl;
    }
}
void SendFunc(int _clntSocket)
{
    std::string message;
    while (true)
    {
        std::cin >> message;
        ssize_t sendSize = write(_clntSocket, message.data(), message.length());
        // std::cout << "SendFucn" << std::endl;
    }
}
int main()
{
    int servSocket{};
    servSocket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    int port{};
    std::cout << "请输入端口号：";
    std::cin >> port;
    servAddr.sin_port = htons(port);
    if (bind(servSocket, (SOCKADDR *)&servAddr, sizeof(servAddr)) == -1)
    {
        std::cerr << "bind() failed\n";
        close(servSocket);
    }
    if (listen(servSocket, 16) == -1)
    {
        std::cerr << "listen() failed\n";
        close(servSocket);
    }
    int clntSocket{};
    SOCKADDR_IN clntAddr{};
    socklen_t addrLen = sizeof(clntAddr);
    if ((clntSocket = accept(servSocket, (struct sockaddr *)&servAddr, &addrLen)) == -1)
    {
        std::cerr << "accept() failed\n";
        close(servSocket);
    }
    char buffer[BUFFERSIZE]{""};
    std::thread readThread(ReadFunc, clntSocket, buffer, BUFFERSIZE);
    std::thread sendThread(SendFunc, clntSocket);
    readThread.detach();
    sendThread.detach();
    std::this_thread::sleep_for(std::chrono::seconds(60));
    //*******************
}
