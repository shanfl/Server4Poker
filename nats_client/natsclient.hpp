#pragma once
#include <string>
#include <memory>
#include "uvw.hpp"
#include <iostream>
#include <map>
#include <unordered_map>
#include "snowflake.hpp"
#include <functional>
#include <thread>

namespace uvw
{
    struct natsclient_t{
        void*data = nullptr;
    };

    enum msg_type
    {
        INFO,
        MSG,
        PING,
        PONG,
        OK,
        ERR
    };

    struct data_base
    {
        msg_type t;
        virtual ~data_base(){}
    };

    struct info_data:public data_base
    {
        std::string server_id;
        std::string server_name;
        std::string go;
        std::string host;
        std::string port;
        bool headers;
        int max_payload;
        int proto;
        uint64_t client_id;
        bool auth_required;
        bool tls_required;
        bool tls_verify;
        bool tls_available;
        std::vector<std::string> connect_urls;
        std::vector<std::string>ws_connect_urls;
        bool ldm;
        std::string git_commit;
        bool jetstream;
        std::string ip;
        std::string client_ip;
        std::string nonce;
        std::string cluster;
        std::string domain;
    };

    struct msg_data:public data_base
    {
        std::string subject;
        std::string sid;
        std::string reply_to ;
        int bytes_len;
        std::string payload;
    };

    struct ping_data:public data_base
    {
    };

    struct pong_data:public data_base
    {
    };

    struct ok_data:public data_base
    {
    };

    struct err_data:public data_base
    {
        std::string err_msg;
    };


    struct connect_data
    {
        bool verbose = false;       // dont replay "+OK"
        bool pedantic;
        bool tls_required;
        std::string auth_token;
        std::string user;
        std::string pass;
        std::string name;
        std::string lang;
        std::string version;
        int protocol;
        bool echo;
        std::string sig;
        std::string jwt;
        bool no_responders;
        bool headers;
        std::string nkey;
    };

    class nats_client;
    using NATS_CALLBACK     = std::function<void(std::shared_ptr<nats_client> client,std::string subject,std::string payload,std::string reply_to)>;


    enum NatsState
    {
        NONE,
        CONNECTING,
        CONNECTED,
        CLOSING,
        CLOSED,
        };

    struct Request
    {
        Request()
        {

        }

        Request(std::string _sub_req,std::string _reply_to,std::string _sid,std::chrono::microseconds _ms_to,NATS_CALLBACK _cb){
            subject_request = _sub_req;
            subject_reply_to = _reply_to;
            sid = _sid;
            timeout = _ms_to;
            start_time = std::chrono::steady_clock::now();
            cb = _cb;
        }
        NATS_CALLBACK cb;
        std::string subject_request;
        std::string subject_reply_to;
        std::string sid;
        std::chrono::microseconds timeout = std::chrono::microseconds(1000*60*2);
        std::chrono::steady_clock::time_point start_time;
    };
}   // namespace uvw

namespace uvw
{
    struct info_event_nats
    {
        info_data data;
    };

    struct msg_event_nats
    {
        msg_data data;
    };

    struct ping_event_nats
    {
        ping_data data;
    };

    struct pong_event_nats
    {
        pong_data data;
    };

    struct ok_event_nats
    {
        ok_data data;
    };

    struct error_event_nats
    {
        err_data data;
    };


    class nats_client:public uvw::resource<uvw::nats_client,natsclient_t,
                                             info_event_nats,msg_event_nats,ping_event_nats,pong_event_nats,ok_event_nats,error_event_nats>
    {
    public:
        nats_client(uvw::loop::token token, std::shared_ptr<uvw::loop> parent,int centerid,int mathineid);

        void connect(std::string host,int port,bool keep = true);
        void disconnect();

        void sub(std::string subject);
        void sub_with_queuegruop(std::string subject,std::string queue_group);
        void set_sub_callback(NATS_CALLBACK cb);

        //void unsub(std::string subject);
        void unsub(std::string sid,int max_msgs = 0);


        void pub(std::string subject,std::string msg);
        void pub_with_reply(std::string subject,std::string msg,std::string replay_to);


        void request_reply(std::string subject,std::string reqmsg,
                     NATS_CALLBACK cb,std::chrono::microseconds timeout);


        void ping();
        void pong();
        void send_connect_data(connect_data data);
        NatsState getState();
        void set_uv_thdid(std::thread::id id);
    protected:
        std::string str_sub(std::string subject,std::string sid);
    protected:
        std::function<void(std::string,std::string,std::string)> mHandleOnSubject;

    protected:
        void setState(NatsState state);
        void raw_send(const char*data,size_t len);
        void raw_send(std::string &str);
        int _connect(std::string host,int port);
        void _reconnect_delay(int ms);
        void _disconnect();
        void sub(std::string subject,std::string sid);
        void sub_with_queuegroup(std::string subject,std::string sid,std::string queue_group);
        void _raw_send(const char*data,size_t len);
        void _raw_send(std::string&str);

        std::string next_sid();
    private:
        std::thread::id mUvMainThdId;
        NatsState mState;
        std::shared_ptr<uvw::tcp_handle> mTcpHanle;
        std::string mData;
        std::string mHost;
        int mPort = 4222;
        bool mKeepConnect = false;

    private:

        // sid -> <subject,queue_group>
        NATS_CALLBACK mSubjectCallback;
        std::map<std::string,std::pair<std::string,std::string>> mSidSubjectsMap;
        std::map<std::string,Request> mReqestMap;

        snowflake<1716253976000L,std::mutex> mSnowFlake;

        int mCenterId = 0;
        int mMachineId = 0;
    private:
        enum OpcodeAsync
        {
            CONNECT,
            DISCONNECT,
            RECONNECT,
            SEND,
            };

        struct AsyncItem{
            OpcodeAsync opcode;
            std::tuple<std::string,int,bool> connect;
            std::string data_send;
        };

        std::vector<AsyncItem> mOpQueue;
        std::mutex mMutexOpQueue;
        std::shared_ptr<uvw::async_handle> mAsync;

        std::shared_ptr<uvw::timer_handle> mTimerReconnect;
    };


} // namespace uvw
