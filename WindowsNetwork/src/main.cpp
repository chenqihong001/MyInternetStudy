#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

int main()
{
    // 初始化 Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        std::cerr << "Failed to initialize Winsock\n";
        return 1;
    }

    // 输入的字符串形式的地址
    LPWSTR addressString = L"192.168.1.1";

    // 输出的地址结构体
    SOCKADDR_STORAGE sockaddr;
    int sockaddrLength = sizeof(sockaddr);

    // 调用 WSAStringToAddressW
    int result = WSAStringToAddressW(
        addressString,
        AF_INET, // 使用 IPv4
        NULL,
        reinterpret_cast<LPSOCKADDR>(&sockaddr),
        &sockaddrLength);

    if (result == 0)
    {
        std::cout << "Address conversion successful\n";
        // sockaddr 中包含了转换后的地址信息
    }
    else
    {
        std::cerr << "WSAStringToAddressW failed with error code: " << WSAGetLastError() << "\n";
    }

    // 清理 Winsock
    WSACleanup();

    return 0;
}
