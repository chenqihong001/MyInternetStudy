#include <arpa/inet.h>
#include <iostream>
int main()
{
    char buffer[1024]{0};
    buffer[0] = '0';
    buffer[1] = '2';
    buffer[2] = 'j';
    buffer[3] = '5';
    std::cout << buffer;
}