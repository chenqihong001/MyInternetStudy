#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
const int BUFFER_SIZE = 1024; // default
int main(int argc, char *argv[])
{
    // socker
    // init sockadrr_in
    // bind
    // recvfrom
    // sendto
    // close
    int servSocket = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY; // htonl(INADDR_ANY);
    std::cout << "请输入端口号：";
    std::string port;
    std::cin >> port;
    addr.sin_port = htons(atoi(port.c_str()));
    if (bind(servSocket, (struct sockaddr *)&addr, sizeof(addr)) == -1)
        std::cerr << "bind failed" << std::endl;
    char buf[BUFFER_SIZE]{};
    int str_len{};
    socklen_t sockLenth{};
    sockLenth = sizeof(addr);
    std::cout << "断点1";
    for (int i = 0; i < 100000; i++)
    {
        str_len = recvfrom(servSocket, buf, BUFFER_SIZE, 0, (struct sockaddr *)&addr, &sockLenth);
        sendto(servSocket, buf, str_len, 0, (struct sockaddr *)&addr, sockLenth);
    }
    close(servSocket);
    return 0;
}
