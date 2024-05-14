#pragma once
#include <string>
#include <iostream>
#include "Msg.def.h"
namespace Base {

#define ROOT_MSG_FUNCTION_BEGIN()          \
virtual void on_msg(Message &x){      \
    switch(x.MsgId()){                 


#define ROOT_MSG_FUNCTION_END() \ 
        default:    \
            std::cout << "not handled" << std::endl; break;   \
    }   \
    }

/*


#define GEN_MESSAGE_MAP(XX) \
	XX(MSG_LOGIN_REQUEST, LoginReq) \
	XX(MSG_LOGIN_REPLY, LoginAck) 


Message* createMessageBy(MessageID msgid)
{
    // 这个switch/case经过宏展开以后跟上面的switch/case其实是一样的
    switch (msgid)
    {
#define XX(msgid, msgname) case msgid: return new msgname;
        GEN_MESSAGE_MAP(XX)
#undef XX
    };
    return nullptr;
}
*/


#define MSG_FUNCTION_BEGIN(SUPERCLASS) \
    virtual void on_msg(Message &x) override {      \
    switch(x.MsgId()){   

#define MSG_FUNCTION_END(SUPERCLASS) \ 
        default:    \
            SUPERCLASS::on_msg(x)    \
    }

class Thread;

class ServerBase
{
private:
    std::vector<std::shared_ptr<Thread>> mThreads;  
public:
    ServerBase(int argc,char*argv[]);
public:
    bool add_timer(int timerid,int delay,int interval);
    bool rem_timer(int timerid);

    bool add_fs(std::string path);
    bool rem_fs(std::string path);

    virtual bool init();
    bool run();
    
    bool listen(std::string ip,int port);

    std::shared_ptr<ProtoMsgLite> create_msg_by_id(uint32_t msgid);

    void on_raw_msg(std::string &data){
        Message msg = Message::Decode(data);
        msg.SetProtoPtr(create_msg_by_id(msg.MsgId()));                
    }

    // 分配到哪个线程
    virtual int dispatch_thd(Message &msg);
    void dispatch_work(Message &msg);


    ROOT_MSG_FUNCTION_BEGIN()
    ROOT_MSG_FUNCTION_END()
};

} //namespace Base