#ifndef CHATSERVER_H
#define CHATSERVER_H
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
using namespace muduo;
using namespace muduo::net;
class ChatServer
{
public:
    ChatServer(EventLoop *loop ,/*事件循环*/
               const InetAddress &listenAddr ,/*IP+Port*/
               const std::string &nameArg /*服务器的名字*/);
    void Start();

private:
    void onConnection(const TcpConnectionPtr &conn);
    void onMessage(const TcpConnectionPtr &conn ,/*连接*/
                   Buffer *buffer ,/*缓冲区*/
                   Timestamp timestamp /*接受到数据的时间*/);

private:
    TcpServer server_; //组合的muduo库，实现服务器功能的类对象
    EventLoop *loop_;  //指向事件循环的对象的指针
};
#endif