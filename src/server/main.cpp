#include "chatserver.hpp"
#include <iostream>
int main()
{
    EventLoop loop; // epoll
    InetAddress address("127.0.0.1", 6000);

    ChatServer server(&loop, address, "ChatServer");
    server.Start();
    loop.loop(); // 以阻塞的方式等待新用户连接
    return 0;
}