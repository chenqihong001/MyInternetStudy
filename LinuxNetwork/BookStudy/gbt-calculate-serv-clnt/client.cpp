#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    // 创建客户端Socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1)
    {
        std::cerr << "Error creating socket\n";
        return -1;
    }

    // 设置服务器地址结构
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // 服务器IP地址
    serverAddr.sin_port = htons(8080);                   // 服务器端口

    // 连接到服务器
    if (connect(clientSocket, reinterpret_cast<sockaddr *>(&serverAddr), sizeof(serverAddr)) == -1)
    {
        std::cerr << "Error connecting to server\n";
        close(clientSocket);
        return -1;
    }

    // 输入数字个数和数字数组
    int numCount;
    std::cout << "Enter the number of elements: ";
    std::cin >> numCount;

    int *numbers = new int[numCount];
    std::cout << "Enter " << numCount << " numbers:\n";
    for (int i = 0; i < numCount; ++i)
    {
        std::cin >> numbers[i];
    }

    // 输入运算符
    char op;
    std::cout << "Enter the operator (+, -, *, /): ";
    std::cin >> op;

    // 发送数字个数
    send(clientSocket, &numCount, sizeof(numCount), 0);

    // 发送数字数组
    send(clientSocket, numbers, sizeof(int) * numCount, 0);

    // 发送运算符
    send(clientSocket, &op, sizeof(op), 0);

    // 接收结果
    int result;
    recv(clientSocket, &result, sizeof(result), 0);

    // 输出结果
    std::cout << "Result received from server: " << result << "\n";

    // 关闭连接和Socket
    close(clientSocket);

    delete[] numbers;

    return 0;
}
