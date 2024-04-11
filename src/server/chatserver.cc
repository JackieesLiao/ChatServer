#include "chatserver.hpp"
#include "chatservice.hpp"
#include "json.hpp"
#include <functional>
#include <iostream>
using json = nlohmann::json;
// 初始化聊天服务器对象
ChatServer::ChatServer(EventLoop *loop,               /*事件循环*/
                       const InetAddress &listenAddr, /*IP+Port*/
                       const std::string &nameArg /*服务器的名字*/)
    : server_(loop, listenAddr, nameArg), loop_(loop)
{
    // 给服务器注册用户连接的创建和断开回调
    server_.setConnectionCallback(std::bind(&ChatServer::onConnection, this, std::placeholders::_1));
    // 给服务器注册用户读写事件回调
    server_.setMessageCallback(std::bind(&ChatServer::onMessage, this, std::placeholders::_1, std::placeholders::_2,
                                         std::placeholders::_3));

    // 设置服务器端的线程数量 设置一个I/O线程,三个工作线程
    server_.setThreadNum(4);
}
// 启动服务
void ChatServer::Start()
{
    server_.start();
}

// 回调函数：专门处理用户的连接创建和断开 epoll listenfd accept
void ChatServer::onConnection(const TcpConnectionPtr &conn)
{
    if (conn->connected())
    {
        std::cout << conn->peerAddress().toIpPort() << "->" << conn->localAddress().toIpPort() << "state online " << std::endl;
    }
    else
    {
        std::cout << conn->peerAddress().toIpPort() << "->" << conn->localAddress().toIpPort() << "state offline  " << std::endl;
        conn->shutdown(); // 关闭fd,客户端断开连接
    }
}
// 回调函数：专门处理用户的读写事件
void ChatServer::onMessage(const TcpConnectionPtr &conn, /*连接*/
                           Buffer *buffer,               /*缓冲区*/
                           Timestamp timestamp /*接受到数据的时间*/)
{
    std::string buff = buffer->retrieveAllAsString();
    // std::cout << "recv data :" << buff << "time:" << timestamp.toString() << std::endl;
    // 数据反序列化
    json js = json::parse(buff);
    //通过js["msgid"]取出msgid获取相应业务handler
    auto handler = ChatService::GetInstance()->GetHandler(js["msgid"].get<int>());
    //回调消息绑定好的事件处理器，来执行相应的业务处理
    handler(conn, js, time);
    conn->send(buff);
}