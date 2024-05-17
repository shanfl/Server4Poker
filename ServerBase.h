#pragma once
#include <string>
#include <iostream>
#include "Msg.def.h"
#include "uvw.hpp"
#include "TimerListener.hpp"
#include <unordered_map>
#include "Session/Session.hpp"
#include "WrappedMessage.hpp"
#include "toml/toml.h"
#include "gen_proto/Base.pb.h"

namespace Base {

#define ROOT_MSG_FUNCTION_BEGIN()          \
virtual void on_msg(std::shared_ptr<uvw::Session> session, Message &x){      \
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

#define ROOT_GEN_MESSAGE_MAP(XX) \
    XX(Pb::Base, ID_HELLO,Hello,On,1)      \
    XX(Pb::Base, ID_PING,Ping,On,0)         \
    XX(Pb::Base, ID_PONG,Pong,On,1)



#define MSG_FUNCTION_BEGIN(SUPERCLASS) \
    virtual void on_msg(std::shared_ptr<uvw::Session> session, Message &x) override {      \
    switch(x.MsgId()){   

#define MSG_FUNCTION_END(SUPERCLASS) \
        default:    \
            SUPERCLASS::on_msg(session,x)    \
    }




/*
 *
 *
 * less is more
 *
 *
 */

#if 0
#define BEGIN_TABLE(CLS) \
    typedef void (CLS::* cls_fn)(std::shared_ptr<uvw::Session>,Message&); \
    using msg_fn = (CLS::*)(std::shared_ptr<uvw::Session>,Message&) \
    using mk_proto_fn = std::function<std::shared_ptr<ProtoMsg>(int id)>; \
    struct msg_call_t \
    {                   \
        int id;         \
        msg_fn fn;      \
        mk_proto_fn mkfn;   \
    } ;

#define MSG_DEF(ID,CLS,FN)
#endif



// kinds of server


class Thread;
class ServerBase : public TimerAlloc
{
    friend class Thread;
    friend class TimerAlloc;
private:
    constexpr static size_t MAX_SERVE_TYPE_CNT = 40;

    std::string mAppPath;
    std::string mTomlCfg;
    std::string mLogFile;
    std::string mNameServer;
    int         mTypeServer = 0;
private:
    // session
    std::unordered_map<int64_t,std::shared_ptr<uvw::Session>> mSessionUndefined;
    std::unordered_map<int64_t,std::shared_ptr<uvw::Session>> mSessions[MAX_SERVE_TYPE_CNT];
    std::mutex mSessionsMutex;

    // undef -> sessions
    void def_session_type(std::shared_ptr<uvw::Session> session,int stype);
private:
    std::shared_ptr<uvw::loop> mLoop;
    std::shared_ptr<uvw::tcp_handle> mTcpHander;
private:
    std::vector<std::shared_ptr<Thread>> mThreads;
    int mIdxLastSet = -1;
    int next_thd_idx();
public:
    ServerBase();
public:
    std::string app_path() {return this->mAppPath;}

    virtual bool init(int argc,char*argv[]);

    // ======================== timer ========================
    virtual void on_timer_tick(int id,int delay,int interval) override;

    int  thd_idx_timer() override {
        return -1;  // mainloop
    }
    //TODO:
    bool add_fs(std::string path);
    bool rem_fs(std::string path);

    bool run();
    
    bool listen(std::string ip,int port);

    void stop();

    std::shared_ptr<uvw::loop> loop() {return mLoop;}
protected:

    //TODO:
    virtual bool init_db(const toml::Value& root);
    virtual bool init_thd(const toml::Value& root);
    virtual bool init_module(const toml::Value& root);
    virtual bool init_nats(const toml::Value& root);
    virtual bool init_serve(const toml::Value& root);
    virtual bool post_init(const toml::Value& root);

    virtual void on_session_close(std::shared_ptr<uvw::Session> session){}

    virtual void on_raw_msg(std::shared_ptr<uvw::Session> session,std::string data);

    // 分配到哪个线程
    virtual int calc_thd_idx(std::shared_ptr<uvw::Session> session,Message&msg);

    void dispatch_th_work(int idx,WrappedMessage &msg);

    ROOT_MSG_FUNCTION_BEGIN()
#define XX(ns,id,cls,prefix,ifCt)   case ns::id: this->prefix##_##cls(session,x);break;
    ROOT_GEN_MESSAGE_MAP(XX)
#undef XX
    ROOT_MSG_FUNCTION_END()

public:
    // declare memfn as on_hello on_ping ...
#define XX(ns,id,cls,prefix,ifCt) void prefix##_##cls(std::shared_ptr<uvw::Session> session, Message&msg);

    ROOT_GEN_MESSAGE_MAP(XX)
#undef XX


    // create_msg_by_id
    std::shared_ptr<ProtoMsg> create_msg_by_id(uint32_t msgid){
        std::shared_ptr<ProtoMsg> ret;
        switch(msgid){
#define XX(ns,id,cls,prefix,ifCt)  case ns::id: ret = std::make_shared<ns::cls>(ns::cls::default_instance());break;
        ROOT_GEN_MESSAGE_MAP(XX)
#undef XX
        default:
            break;
        }
        return ret;
    }

#undef ROOT_GEN_MESSAGE_MAP
};

} //namespace Base
