#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
void ErrorHandling(std::string str);
void CalculatePackage(int num, char _operator, char *data, size_t bufferSize);

int main()
{
    int clntSocket{};
    clntSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clntSocket == -1)
        ErrorHandling("socket");
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    std::string servIp{};
    std::cout << "请输入服务器IP:";
    std::cin >> servIp;
    addr.sin_addr.s_addr = inet_addr(servIp.c_str());
    std::string _port;
    std::cout << "请输入端口号....";
    std::cin >> _port;
    addr.sin_port = htons(atoi(_port.c_str()));
    if (connect(clntSocket, (struct sockaddr *)&addr, sizeof(addr)) == -1)
        ErrorHandling("connect");
    //************
    const size_t bufferSize = 1024;
    char *datas = new char[bufferSize];
    int num{};
    std::cout << "请输入需要计算的数据的个数 >> \n";
    std::cin >> num;
    std::cout << "请输入需要进行的运算(+,-,*,/) >> \n";
    char _operator{};
    std::cin >> _operator;
    // 使用 datas 缓冲区
    CalculatePackage(num, _operator, datas, bufferSize);
    send(clntSocket, datas, sizeof(int) * (num + 1) + sizeof(char), 0);
    int result{};
    recv(clntSocket, &result, sizeof(int), 0);
    std::cout << "The Result From Server is :" << result << std::endl;
    delete[] datas;
    close(clntSocket);
    return 0;
}

void ErrorHandling(std::string str)
{
    std::cout << str << "()Error" << std::endl;
    exit(1);
}
void CalculatePackage(int num, char _operator, char *data, size_t bufferSize)
{
    memcpy(data, &num, sizeof(num));
    std::cout << "请输入你要输入的" << num << "个数据\n";
    for (int i = 0; i < num; i++)
    {
        int val;
        std::cin >> val;
        size_t offset = sizeof(int) + sizeof(int) * i;
        memcpy(data + offset, &val, sizeof(int));
    }
    // 计算最终偏移量并将运算符写入缓冲区
    size_t finalOffset = sizeof(int) * (num + 1);
    memcpy(data + finalOffset, &_operator, sizeof(char));
}
