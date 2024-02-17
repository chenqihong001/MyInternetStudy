#include <iostream>
#include <unistd.h>
#include <sys/epoll.h>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
constexpr int MAX_EVENTS = 10;
constexpr int BUFFER_SIZE = 1024;

int main()
{
    // 创建监听套接字
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1)
    {
        perror("socket");
        return 1;
    }

    // 绑定地址和端口
    sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(8080);
    if (bind(server_fd, reinterpret_cast<sockaddr *>(&server_addr), sizeof(server_addr)) == -1)
    {
        perror("bind");
        close(server_fd);
        return 1;
    }

    // 监听连接
    if (listen(server_fd, 5) == -1)
    {
        perror("listen");
        close(server_fd);
        return 1;
    }

    // 创建 epoll 实例
    int epoll_fd = epoll_create1(0);
    if (epoll_fd == -1)
    {
        perror("epoll_create1");
        close(server_fd);
        return 1;
    }

    // 添加监听套接字到 epoll 实例中
    epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = server_fd;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &event) == -1)
    {
        perror("epoll_ctl");
        close(server_fd);
        close(epoll_fd);
        return 1;
    }

    // 创建事件数组
    epoll_event events[MAX_EVENTS];

    while (true)
    {
        // 等待事件发生
        int num_events = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        if (num_events == -1)
        {
            perror("epoll_wait");
            break;
        }

        // 处理事件
        for (int i = 0; i < num_events; ++i)
        {
            if (events[i].data.fd == server_fd)
            {
                // 有新的连接请求
                sockaddr_in client_addr;
                socklen_t client_len = sizeof(client_addr);
                int client_fd = accept(server_fd, reinterpret_cast<sockaddr *>(&client_addr), &client_len);
                if (client_fd == -1)
                {
                    perror("accept");
                    continue;
                }

                // 将客户端套接字添加到 epoll 实例中
                event.events = EPOLLIN;
                event.data.fd = client_fd;
                if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &event) == -1)
                {
                    perror("epoll_ctl");
                    close(client_fd);
                }
            }
            else
            {
                // 读取客户端数据并回送
                char buffer[BUFFER_SIZE];
                int bytes_received = recv(events[i].data.fd, buffer, BUFFER_SIZE, 0);
                if (bytes_received <= 0)
                {
                    if (bytes_received == 0)
                    {
                        std::cout << "Client disconnected" << std::endl;
                    }
                    else
                    {
                        perror("recv");
                    }
                    close(events[i].data.fd);
                    continue;
                }

                // 发送回送数据
                int bytes_sent = send(events[i].data.fd, buffer, bytes_received, 0);
                if (bytes_sent == -1)
                {
                    perror("send");
                    close(events[i].data.fd);
                }
            }
        }
    }

    // 关闭套接字和 epoll 实例
    close(server_fd);
    close(epoll_fd);

    return 0;
}
