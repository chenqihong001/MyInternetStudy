/*地址族和数据序列*/
// 分配给套接字的IP地址与端口号
// 网络地址-> 1.ipv4 2.ipv6 = 网络ID + 主机ID
// TCP套接字和UDP套接字不会共用端口号,可分配端口号范围0-65535
// 网络字节序->统一为大端序
// inet_addr()有检测错误的能力，可以将IP地址转换为32整型，同时能够转换为网络字节序
// inet_aton()与inet_addr()作用相同
// inet_ntoa();把网络字节序整数转换为字符串->每次会返回同一个静态内存区，注意数据覆盖
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
typedef struct sockaddr_in SOCKADDR_IN;
int main()
{
    std::string addrStr = "127.0.0.1";
    std::string addrStr2 = "122.45.0.1";
    SOCKADDR_IN clientAddr, serverAddr;
    u_long num = inet_addr(addrStr.c_str());
    inet_aton(addrStr.c_str(), &clientAddr.sin_addr);
    inet_aton(addrStr2.c_str(), &serverAddr.sin_addr);
    if (num == INADDR_NONE)
    {
        // std::cout << "ERROR!" << std::endl;
    }

    // std::cout << num << "\n";.
    //  把网络字节序整数转换为字符串
    char *str = inet_ntoa(clientAddr.sin_addr);
    // std::cout << str << std::endl;
    char *str2 = inet_ntoa(serverAddr.sin_addr);
    // std::cout << str << std::endl;

    SOCKADDR_IN sockAddr{}; // 网络地址结构体
    unsigned char it = sockAddr.sin_zero[0];
    std::cout << static_cast<int>(it) << "结束" << std::endl;

    // std::cout << it;
}
