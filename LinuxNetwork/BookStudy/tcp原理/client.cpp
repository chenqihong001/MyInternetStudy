#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>
const int BUFFERSIZE = 1024;
void ErrorHandling(const char *message)
{
    std::cout << message << std::endl;
}
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
        std::cout << "来自服务端：" << _buffer << std::endl;
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
    int clntSocket{};
    clntSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clntSocket == -1)
    {
        ErrorHandling("socket()Error");
        close(clntSocket);
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int _port{};
    std::cout << "请输入端口号：";
    std::cin >> _port;
    addr.sin_port = htons(_port);
    if (connect(clntSocket, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        ErrorHandling("connect()Error");
        close(clntSocket);
    }
    //************************
    char buffer[BUFFERSIZE]{""};
    std::thread readThread(ReadFunc, clntSocket, buffer, BUFFERSIZE);
    std::thread sendThread(SendFunc, clntSocket);
    readThread.detach();
    sendThread.detach();
    std::this_thread::sleep_for(std::chrono::seconds(60));
    return 0;
}