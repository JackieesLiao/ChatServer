#include <iostream>
#include <string>
#include <functional>
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
using namespace muduo::net;
using namespace muduo;

// muduo库
// epoll + 线程池 :能够把网络IO的代码与业务代码区分开
// 可调用类 ： TcpServer  TcpClient

// 1.组合tcpserver对象
// 2.创建Eventloop事件循环对象的指针
// 3.TcpServer构造函数需要什么参数，chatServer的构造函数也是如此
// 4.在当前服务器的构造函数中,注册会处理连接的回调函数以及处理读写事件的回调函数
// 5.设置合适的服务端线程数量,muduo库会自动划分I/O线程与worker线程
class ChatServer
{
public:
    ChatServer(EventLoop *loop ,/*事件循环*/
               const InetAddress &listenAddr ,/*IP+Port*/
               const std::string &nameArg /*服务器的名字*/) : server_(loop, listenAddr, nameArg), loop_(loop)
    {
        // 给服务器注册用户连接的创建和断开回调
        server_.setConnectionCallback(std::bind(&ChatServer::onConnection, this, std::placeholders::_1));
        // 给服务器注册用户读写事件回调
        server_.setMessageCallback(std::bind(&ChatServer::onMessage, this, std::placeholders::_1, std::placeholders::_2,
                                             std::placeholders::_3));

        // 设置服务器端的线程数量 设置一个I/O线程,三个工作线程
        server_.setThreadNum(4);
    }
    // 开启事件循环
    void Start()
    {
        server_.start();
    }

private:
    // 专门处理用户的连接创建和断开 epoll listenfd accept
    void onConnection(const TcpConnectionPtr &conn)
    {
        if (conn->connected())
        {
            std::cout << conn->peerAddress().toIpPort() << "->" << conn->localAddress().toIpPort() << "state online " << std::endl;
        }
        else
        {
            std::cout << conn->peerAddress().toIpPort() << "->" << conn->localAddress().toIpPort() << "state offline  " << std::endl;
            conn->shutdown(); // 关闭fd
            // loop_->quit();
        }
    }
    // 专门处理用户的读写事件
    void onMessage(const TcpConnectionPtr &conn ,/*连接*/
                   Buffer *buffer ,/*缓冲区*/
                   Timestamp timestamp /*接受到数据的时间*/)
    {
        std::string buff = buffer->retrieveAllAsString();
        std::cout << "recv data :" << buff << "time:" << timestamp.toString() << std::endl;
        conn->send(buff);
    }

private:
    TcpServer server_;
    EventLoop *loop_; // epoll
};

int main()
{
    EventLoop loop; // epoll
    InetAddress address("127.0.0.1", 6000);

    ChatServer server(&loop, address, "ChatServer");
    server.Start();
    loop.loop(); // 以阻塞的方式等待新用户连接
}

//编译运行此代码  :  g++ -std=c++17 -o server muduo_server.cc -lmuduo_net -lmuduo_base -lpthread 
//另一个终端输入 telnet 127.0.0.1 6000