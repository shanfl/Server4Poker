#pragma once
#include <string>
#include <iostream>
#include "Msg.def.h"
#include "WrappedMessage.hpp"
#include "uvw.hpp"
#include "TimerListener.hpp"
#include <unordered_map>
#include "Session/Session.hpp"
#include "tinytoml/toml.h"
#include "gen_proto/Base.pb.h"
#include "nats_client/natsclient.hpp"
#include <set>
#include <shared_mutex>



namespace Base {

	struct MSG_BIND_ITEM
	{
		MSG_BIND_ITEM(const ProtoMsg* msginstance, SESSION_FN fn) :msg_default_instance(msginstance) {
			fn_session = fn;
		}

		MSG_BIND_ITEM() {}

		const ProtoMsg* msg_default_instance = nullptr;
		SESSION_FN fn_session = nullptr;
		NATS_FN    fn_nats = nullptr;
	};

#define BEGIN_MSG_MAP_ROOT(THIS_CLASS) \
    using this_class = THIS_CLASS;  \
    virtual void init_pb()  {

// #define BIND_MSG(PBNAMESPACE,ID,MSG_CLASS) \
//     mBindMsgs[PBNAMESPACE::ID] = MSG_BIND_ITEM(                         \
//         PBNAMESPACE::MSG_CLASS::internal_default_instance(),            \
//         std::bind(&this_class::on_msg_##MSG_CLASS,this,std::placeholders::_1,std::placeholders::_2) \
//     );

#define BIND_SESSION_MSG(PBNAMESPACE,ID,MSG_CLASS) \
    mBindMsgs[PBNAMESPACE::ID].msg_default_instance     = PBNAMESPACE::MSG_CLASS::internal_default_instance();                   \
    mBindMsgs[PBNAMESPACE::ID].fn_session               = std::bind(&this_class::on_msg_##MSG_CLASS,this,std::placeholders::_1,std::placeholders::_2);


#define BIND_NATS_MSG(PBNAMESPACE,ID,MSG_CLASS) \
    mBindMsgs[PBNAMESPACE::ID].msg_default_instance     = PBNAMESPACE::MSG_CLASS::internal_default_instance();                   \
    mBindMsgs[PBNAMESPACE::ID].fn_nats                  = std::bind(&this_class::on_natspub_##MSG_CLASS,this,std::placeholders::_1,std::placeholders::_2);

#define END_MSG_MAP_ROOT() }


#define BEGIN_MSG_MAP(THIS_CLASS,SUPER_CLASS) \
using this_class = THIS_CLASS;  \
    virtual void init_pb()  { SUPER_CLASS::init_pb();


#define END_MSG_MAP() }


	/*
	 *
	 *
	 * less is more
	 *
	 *
	 */


    enum class LogLevel : int8_t
    {
        debug,
        info,
        warn,
        err,
        critical,
    };

	static const int MIN_USER_TIMERID = 1000;

    static const int TIMERID_SESSION_CHECK  = 1;        // 检查session的timer
    static const int TIMERID_NATS_CHECK     = 2;        // 检查nats的timer

	class Thread;
	class ServerBase : public TimerAlloc
	{
		friend class Thread;
		friend class TimerAlloc;
	public:

		BEGIN_MSG_MAP_ROOT(ServerBase)
		BIND_SESSION_MSG(Pb::Base, ID_HELLO, Hello)
		END_MSG_MAP_ROOT()

		//
		void on_msg_Hello(SessionPtr session, Message& msg) {}

        //void on_natspub_Hello(NatsClinetPtr natsc,Message&msg){}

	public:
		std::unordered_map<int32_t, MSG_BIND_ITEM> mBindMsgs;
	private:
		constexpr static size_t MAX_SERVE_TYPE_CNT = 40;
        bool        mRunning = false;
		std::string mAppPath;
		std::string mTomlCfg;
		std::string mLogFile;
		std::string mName;
		int         mType = 0;
		int         mIndex = 0;

	private:
		std::map<std::string, std::shared_ptr<uvw::nats_client>> mNatsClients;
	private:
		// session
		std::unordered_map<int64_t, std::shared_ptr<uvw::Session>> mSessionUndefined;
		std::unordered_map<int64_t, std::shared_ptr<uvw::Session>> mSessions[MAX_SERVE_TYPE_CNT];
		std::mutex mSessionsMutex;

		// undefined -> defined sessions
		void def_session_type(std::shared_ptr<uvw::Session> session, int stype);
	private:
		std::shared_ptr<uvw::loop> mLoop;
		std::shared_ptr<uvw::tcp_handle> mTcpHander;
	private:
		std::vector<std::shared_ptr<Thread>> mThreads;
		int mIdxLastSet = -1;
		int next_thd_idx();
	public:
		ServerBase();
        ~ServerBase(){ stop();}
	public:
		std::string app_path() { return this->mAppPath; }
		std::string app_name();
		int app_type();
		int app_index();

		virtual bool init(int argc, char* argv[]);

		virtual void on_timer(int id,int delay, int interval) {};

		int thd_idx_timer() override;

		//TODO:
		bool add_fs(std::string path);
		bool rem_fs(std::string path);

		bool run();

		bool listen(std::string ip, int port);

		void stop();

		std::shared_ptr<uvw::loop> loop() { return mLoop; }

		virtual void on_nats_pub(std::shared_ptr<uvw::nats_client> client,
			std::string subject,
			int32_t id,
			std::shared_ptr<ProtoMsg> msg,
			std::string replyto);

        void log(LogLevel ll,std::string str);

        void nats_pub(NatsClinetPtr client,std::string subject,int id,ProtoMsg &msg);
        void nats_reqest_reply(NatsClinetPtr client,std::string subject,int id,ProtoMsg &msg,int mstimout,NatsReqReplyCallBack cb);
    protected:
        // ======================== timer ========================
        void on_timer_tick(int id, int delay, int interval) override;
		//TODO:
		virtual bool init_db(const toml::Value& root);
		virtual bool init_thd(const toml::Value& root);
		virtual bool init_module(const toml::Value& root);
		virtual bool init_nats(const toml::Value& root);
		virtual bool init_serve(const toml::Value& root);
		virtual bool post_init(const toml::Value& root);

		virtual void on_session_close(std::shared_ptr<uvw::Session> session) {}
		virtual void on_raw_msg(std::shared_ptr<uvw::Session> session, std::string data);
		// recv nats's info
		virtual void on_nats_info(std::shared_ptr<uvw::nats_client> client, uvw::info_data data) {}
        virtual void on_nats_raw_sub(std::shared_ptr<uvw::nats_client> client, std::string sub, std::string msg, std::string reply_to,bool timeout = false);

		// 分配到哪个线程
		virtual int calc_session_thd_idx(std::shared_ptr<uvw::Session> session, Message& msg);
		virtual int calc_nats_thd_idx(std::shared_ptr<uvw::nats_client> cli, int32_t msgid, std::shared_ptr<ProtoMsg> msg);
		void dispatch_th_work(int idx, WrappedMessage& msg);

    protected:
        void add_timer_alloc(TimerAlloc* ta);
        void rem_timer_alloc(TimerAlloc* ta);
        virtual void on_ta_timer_tick(TimerAlloc*ac, int id, int delay, int interval);
    private:
        std::set<TimerAlloc*> mTimerAllocs;
        std::shared_mutex mMutexTimerAllocs;          // shared_mutex


    private:
        void on_nats_reqest_reply(NatsClinetPtr client,std::string subject,std::string payload,std::string reply_to,bool istimout);
        std::unordered_map<std::string,std::tuple<NatsReqReplyCallBack,std::thread::id,std::chrono::steady_clock::time_point>> mNats_Request_Reply;
        std::shared_mutex mMutexRequestReply;          // shared_mutex
	};

} //namespace Base
