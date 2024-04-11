#include "chatservice.hpp"
#include "Common.hpp"
using namespace std::placeholders;
//注册消息以及对应的回调函数
ChatService::ChatService()
{
    msgHandler_.insert(std::make_pair(LOGIN_MSG, std::bind(&ChatService::Login, this, _1, _2, _3)));
    msgHandler_.insert(std::make_pair(REGISTER_MSG, std::bind(&ChatService::Register, this, _1, _2, _3)));
}
// 登录业务
void ChatService::Login(const TcpConnectionPtr &conn, json &js, Timestamp time)
{

}
// 注册业务
void ChatService::Register(const TcpConnectionPtr &conn, json &js, Timestamp time)
{

}
//单例模式
ChatService *ChatService::GetInstance()
{
    static ChatService service;
    return &service;
}
//获取消息对应的处理器
MsgHandler ChatService::GetHandler(int msgid) const
{
    if(msgHandler_.find(msgid) != msgHandler_.end()){
        return msgHandler_[msgid];
    }
    else{
        //未找到对应的事件处理回调则记录到日志里
        return [=](const TcpConnectionPtr &conn, json &js, Timestamp){
            LOG_ERROR << "MSG ID:" <<msgid <<"couldn't find handler.";
        }
    }
}