#include <iostream>
#include <thread>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
int Calculate(int num, int *dataArray, char _operator)
{
    int result{};
    std::cout << "收到的信息：" << std::endl;
    std::cout << "数据量:" << num << std::endl;
    std::cout << "符号:" << _operator << std::endl;
    for (int i = 0; i < num; i++)
    {
        switch (_operator)
        {
        case '+':
            result += dataArray[i];
            break;
        case '-':
            result -= dataArray[i];
            break;
        default:
            break;
        }
    }
    return result;
}
int main()
{
    int clntSocket{}, servSocket{};
    servSocket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = INADDR_ANY; // htonl()
    std::string _port;
    std::cout << "请输入端口号....";
    std::cin >> _port;
    servAddr.sin_port = htons(atoi(_port.c_str()));
    if (bind(servSocket, (struct sockaddr *)&servAddr, sizeof(servAddr)) == -1)
        std::cout << "bind()Error" << std::endl;
    if (listen(servSocket, 64) == -1)
        std::cout << "listen()Error" << std::endl;
    // accept()
    struct sockaddr_in clntAddr = {0};
    socklen_t clntAddrSize = sizeof(clntAddr);
    if ((clntSocket = accept(servSocket, (struct sockaddr *)&servAddr, &clntAddrSize)) < 0)
    {
        std::cout << "accept()Error" << std::endl;
    }
    int dataNum{};
    int *dataArray = new int[dataNum];
    char _operator;
    read(clntSocket, &dataNum, sizeof(int));
    for (int i = 0; i < dataNum; i++)
    {
        read(clntSocket, dataArray + i, sizeof(int));
    }
    read(clntSocket, &_operator, sizeof(char));
    std::cout << "接收信息完毕...\n";
    int result = Calculate(dataNum, dataArray, _operator);
    send(clntSocket, &result, sizeof(result), 0);
    delete[] dataArray;
    close(servSocket);
    close(clntSocket);
    return 0;
}