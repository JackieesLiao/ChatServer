#ifndef CHATSERVICE_H
#define CHATSERVICE_H
#include "json.hpp"
#include <muduo/net/TcpConnection.h>
#include <unordered_map>
#include <functional>
using json = nlohmann::json;
using namespace muduo;
using namespace muduo::net;
//表示处理消息的事件回调方法类型
using MsgHandler = std::function<void(const TcpConnectionPtr &conn, json &js, Timestamp)>;
class ChatService 
{
public:
    void Login(const TcpConnectionPtr &conn, json &js, Timestamp time);    
    void Register(const TcpConnectionPtr &conn, json &js, Timestamp time);
    static ChatService *GetInstance();
    //获取消息对应的处理器
    MsgHandler GetHandler(int msgid) const;
private:
    ChatService();
    //存储消息ID和其对应的业务处理方法
    std::unordered_map<int, MsgHandler> msgHandler_;
};

#endif