#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    // 创建服务器Socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1)
    {
        std::cerr << "Error creating socket\n";
        return -1;
    }

    // 设置服务器地址结构
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8080); // 使用8080端口

    // 绑定服务器Socket到地址结构
    if (bind(serverSocket, reinterpret_cast<sockaddr *>(&serverAddr), sizeof(serverAddr)) == -1)
    {
        std::cerr << "Error binding socket\n";
        close(serverSocket);
        return -1;
    }

    // 监听连接
    if (listen(serverSocket, 5) == -1)
    {
        std::cerr << "Error listening on socket\n";
        close(serverSocket);
        return -1;
    }

    std::cout << "Server listening on port 8080...\n";

    // 接受连接
    sockaddr_in clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);
    int clientSocket = accept(serverSocket, reinterpret_cast<sockaddr *>(&clientAddr), &clientAddrSize);
    if (clientSocket == -1)
    {
        std::cerr << "Error accepting connection\n";
        close(serverSocket);
        return -1;
    }

    std::cout << "Connection accepted from " << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << "\n";

    // 接收数字个数
    int numCount;
    recv(clientSocket, &numCount, sizeof(numCount), 0);
    // 接收数字数组
    int *numbers = new int[numCount];
    recv(clientSocket, numbers, sizeof(int) * numCount, 0);

    // 接收运算符
    char op;
    recv(clientSocket, &op, sizeof(op), 0);

    // 进行计算
    int result = 0;
    for (int i = 0; i < numCount; ++i)
    {
        switch (op)
        {
        case '+':
            result += numbers[i];
            break;
        case '-':
            result -= numbers[i];
            break;
        case '*':
            result *= numbers[i];
            break;
        case '/':
            result /= numbers[i];
            break;
        default:
            std::cerr << "Invalid operator\n";
            close(clientSocket);
            close(serverSocket);
            delete[] numbers;
            return -1;
        }
    }

    // 发送结果
    send(clientSocket, &result, sizeof(result), 0);

    // 关闭连接和Socket
    close(clientSocket);
    close(serverSocket);

    delete[] numbers;

    return 0;
}
