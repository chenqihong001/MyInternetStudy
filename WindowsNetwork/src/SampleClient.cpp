#include <iostream>
#include <WinSock2.h>
int main(int argc, char *argv[])
{
    WSADATA wsaData;
    SOCKET clientSocket;
    SOCKADDR_IN clientAddr;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_addr.s_addr = inet_addr(argv[1]);
    clientAddr.sin_port = htons(atoi(argv[2]));
    connect(clientSocket, (SOCKADDR *)&clientAddr, sizeof(clientAddr));
    char buf[1024]; // 接收信息的缓冲区
    int messageSize = recv(clientSocket, buf, sizeof(buf), 0);
    buf[messageSize] = '\0';
    std::cout << buf << std::endl;
    closesocket(clientSocket);
    WSACleanup();
    return 0;
}