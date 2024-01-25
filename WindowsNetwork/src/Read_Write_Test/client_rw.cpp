#include <iostream>
#include <WinSock2.h>
#include <thread>
int main(int argc, char *argv[])
{
    WSADATA wsaData;
    SOCKADDR_IN clntAddr{};
    SOCKET clnt_sock{};
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    clnt_sock = socket(AF_INET, SOCK_STREAM, 0);
    clntAddr.sin_family = AF_INET;
    clntAddr.sin_addr.s_addr = inet_addr(argv[1]);
    clntAddr.sin_port = htons(atoi(argv[2]));
    connect(clnt_sock, (SOCKADDR *)&clntAddr, sizeof(clntAddr));
    // 信息交流
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::string message = "The Message from Client";
    char buffer[1024]{};
    std::this_thread::sleep_for(std::chrono::seconds(2));
    // 停两秒再发信息
    send(clnt_sock, message.c_str(), sizeof(message), 0);
    // int length = recv(clnt_sock, buffer, 1024, 0);
    // buffer[length] = '\0';
    // std::cout << "客户端收到的信息" << buffer << std::endl;
    //  system("pause");
    system("pause");
    closesocket(clnt_sock);
    return 0;
}