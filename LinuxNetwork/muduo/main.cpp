#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <iostream>

using namespace muduo;
using namespace muduo::net;

// Echo服务器类
class EchoServer
{
public:
    EchoServer(EventLoop *loop, const InetAddress &listenAddr)
        : server_(loop, listenAddr, "EchoServer")
    {
        // 设置当有新连接到来时的回调函数
        server_.setConnectionCallback(
            [](const TcpConnectionPtr &conn)
            {
                if (conn->connected())
                {
                    std::cout << "New connection from " << conn->peerAddress().toIpPort() << std::endl;
                }
                else
                {
                    std::cout << "Connection " << conn->name() << " is down" << std::endl;
                }
            });

        // 设置当有数据到来时的回调函数
        server_.setMessageCallback(
            [](const TcpConnectionPtr &conn, Buffer *buf, Timestamp)
            {
                conn->send(buf->retrieveAllAsString()); // Echo收到的数据
            });
    }

    // 启动服务器
    void start()
    {
        server_.start();
    }

private:
    TcpServer server_; // TCP服务器对象
};

int main()
{
    EventLoop loop;
    InetAddress listenAddr(9877); // 监听端口9877

    EchoServer server(&loop, listenAddr);
    server.start(); // 启动Echo服务器

    loop.loop(); // 开始事件循环

    return 0;
}
