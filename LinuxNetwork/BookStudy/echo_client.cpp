#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
using SOCKADDR = struct sockaddr;
using SOCKADDR_IN = struct sockaddr_in;
int main(int argc, char *arcv[])
{
    int sock{};
    SOCKADDR_IN clntAddr;
    if (argc != 3)
    {
        std::cout << "Argc Num Error!" << std::endl;
        exit(1);
    }
    sock = socket(AF_INET, SOCK_STREAM, 0);
}