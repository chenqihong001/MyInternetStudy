#include <iostream>
#include <WinSock2.h>
void ErrorHandling(std::string str);
int main(int argc, char *argv[])
{
    WSADATA wsaData;
    SOCKET clntSocket, servSocket;
    SOCKADDR_IN servAddr{}, clntAddr{};
    int szClntAddr = sizeof(clntAddr);
    if (argc != 2)
    {
        printf("Usage :%s<port>\n", argv[0]);
    }
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        ErrorHandling("WSAStartup() Error");
    }
    servSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (servSocket == INVALID_SOCKET)
        ErrorHandling("socket() Error");
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(atoi(argv[1]));
    if (bind(servSocket, (SOCKADDR *)&servAddr, sizeof(clntAddr)) == SOCKET_ERROR)
    {
        ErrorHandling("bind()Error");
    }
    if (listen(servSocket, 5) == SOCKET_ERROR)
    {
        ErrorHandling("listen()Error");
    }
    int strLen{}; // 接收的消息长度
    char recvMessage[1024];
    for (int i = 1; i <= 5; i++)
    {
        clntSocket = accept(servSocket, (SOCKADDR *)&servAddr, &szClntAddr);
        if (clntSocket == INVALID_SOCKET)
            ErrorHandling("accept()Errror");
        else
            std::cout << "Successfully Connected :" << i << std::endl;
        while ((strLen = recv(clntSocket, recvMessage, 1024, 0)) > 0)
        {
            send(clntSocket, recvMessage, strLen, 0); // 收一点，发一点
        }

        closesocket(clntSocket);
    }
    closesocket(servSocket);
    WSACleanup();
}
void ErrorHandling(std::string str)
{
    std::cout << "Error:" << str << std::endl;
}