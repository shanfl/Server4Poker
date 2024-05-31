#include "ServerBase.h"
#include "WrappedMessage.hpp"
#include <filesystem>
#include "Thread.hpp"
#include "OptionParser.h"
#include "google/protobuf/descriptor.h"
#include <google/protobuf/descriptor_database.h>
#include "TomlHelper.h"
#include "3rd/string-utils/string_utils.h"

#include "spdlog/spdlog.h"
#include "spdlog/details/registry.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"


static std::shared_ptr<spdlog::logger> g_Logger;

namespace Base {

    ServerBase::ServerBase()
    {
        mLoop = uvw::loop::get_default();

        mTcpHander = mLoop->resource<uvw::tcp_handle>();
	}

    ServerBase::~ServerBase(){
        stop();
    }


	std::string ServerBase::app_name()
	{
		return mName;
	}

	int ServerBase::app_type()
	{
		return mType;
	}

	int ServerBase::app_index()
	{
		return mIndex;
	}

	int  ServerBase::thd_idx_timer() {
		return -1;  // mainloop
	}

    void ServerBase::__on_timer(ITimerListenerWPtr wptr,int id,int interval)
    {
        if(wptr.expired()) return;
        std::shared_ptr<ITimerListener> sptr = wptr.lock();
        if(!sptr) return;
        if(sptr.get() == this){
            this->on_timer_tick(id,interval);
            return;
        }
        int index = sptr->thd_idx_timer();
        this->log(LogLevel::info," index = ", index);
        if(index == 0 || this->mThreads.size() == 0){
            sptr->__on_timer(id,interval,0);
            return;
        }
        else
        {
            WrappedMessage w_msg;
            w_msg.set(wptr,id,interval);
            this->dispatch_th_work(index,w_msg);
        }
    }

    void ServerBase::on_timer_tick(int id,int interval) {
        std::clog << __FUNCTION__ << " id:" << id << ",interval:" << interval << std::endl;
		if(id >= MIN_USER_TIMERID){
            this->on_timer(id,interval);
			return;
		}

		//TODO:
	}

	bool ServerBase::post_init(const toml::Value& root)
	{
		return true;
	}

    void ServerBase::add_timer(int id,int delay,int interval)
    {
        mTimerAlloc.add_timer(id,delay,interval,shared_from_this());
    }

    void ServerBase::rem_timer(int id)
    {
        mTimerAlloc.rem_timer(id);
    }

	bool ServerBase::init(int argc, char* argv[])
	{
        mTimerAlloc.init(this);

		std::string path = std::string(argv[0]);
		std::filesystem::path p(path);
		mAppPath = p.parent_path().string();
        mName = p.filename();

		//-l abc.log -c int.cfg
		using optparse::OptionParser;
		OptionParser parser = OptionParser().description("==core==");
		parser.add_option("-l", "--log").dest("log")
			.help("write  log").metavar("LOG");

        parser.add_option("-t", "--toml").dest("toml")
			.help("toml file").metavar("toml");

		optparse::Values options = parser.parse_args(argc, argv);
		if (options.is_set("log")) {
			mLogFile = options["log"];
		}

		if (options.is_set("toml")) {
			mTomlCfg = options["toml"];
		}
		else {
			std::clog << "cfg file can't find ,return " << std::endl;
			return false;
		}
		std::clog << "cfg:" << mTomlCfg << ",log:" << mLogFile << "\n";

        // --log init --
        if(mLogFile.length() == 0) mLogFile = app_name()+ "_" + std::to_string(time(NULL)) + ".log";
        auto pathf = std::filesystem::path(mLogFile);
        if(pathf.is_relative())
            mLogFile = app_path()+"/" + mLogFile;


		std::vector<spdlog::sink_ptr> sinks;
		sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        sinks.push_back(std::make_shared<spdlog::sinks::daily_file_sink_mt>(mLogFile.c_str(), 23, 59));

		g_Logger = std::make_shared<spdlog::logger>("C", begin(sinks), end(sinks));
		spdlog::register_logger(g_Logger);

		g_Logger->set_level(spdlog::level::trace);
		g_Logger->info("=========================> start <========================= ");
        // --log init --   end
        std::filesystem::path pcfg = std::filesystem::path(mTomlCfg);
        std::string fullpath =  pcfg.is_relative() ? (app_path() + "/" + mTomlCfg):pcfg.string();
        this->log(LogLevel::info," toml:" + fullpath);
		std::ifstream ifs(fullpath);
		toml::ParseResult pr = toml::parse(ifs);
        if (!pr.valid()) {
            this->log(LogLevel::err,"parser toml:" + mTomlCfg + " failed, reason:" + pr.errorReason);
			return false;
		}

		this->mName = TomlHelper::TGet<std::string>(pr.value, "", "name", "unknown");
		this->mType = TomlHelper::TGet<int>(pr.value, "", "type", 0);
		this->mIndex = TomlHelper::TGet<int>(pr.value, "", "index", 0);

		bool r1 = init_thd(pr.value);
		bool r2 = init_db(pr.value);
		bool r3 = init_module(pr.value);
		bool r4 = init_serve(pr.value);
        bool r5 = init_nats(pr.value);
        if (r1 && r2 && r3 && r4 && r5) {
			return post_init(pr.value);
		}
		return false;
	}

	bool ServerBase::init_serve(const toml::Value& root)
	{
		std::string ip = TomlHelper::TGet<std::string>(root, "server", "ip", "0.0.0.0");
		int port = TomlHelper::TGet<int>(root, "server", "port", 8989);

		return listen(ip, port);
	}

	bool ServerBase::init_db(const toml::Value& root)
	{
		return true;
	}

	bool ServerBase::init_thd(const toml::Value& root)
	{
		int ntd = std::thread::hardware_concurrency();
		int cnt_thread = TomlHelper::TGet<int>(root, "thread", "cnt", ntd);
		if (cnt_thread < 0 || cnt_thread > ntd)
			cnt_thread = ntd;

		for (int i = 0; i < cnt_thread; i++)
            mThreads.emplace_back(std::make_shared<Thread>(this, i+1));

		return true;
	}

	bool ServerBase::init_module(const toml::Value& root)
	{
		return true;
	}

	bool ServerBase::init_nats(const toml::Value& root)
	{
		int n = TomlHelper::ArrayGetCnt(root, "nats");
		for (int i = 0; i < n; i++) {
			std::string name = TomlHelper::ArrayGet<std::string>(root, "nats", i, "name", std::to_string(i));
            name == "system" ? name : name += "." + std::to_string(i);
			std::string host = TomlHelper::ArrayGet<std::string>(root, "nats", i, "host", "");
			int port = TomlHelper::ArrayGet<int>(root, "nats", i, "port", 0);
			std::vector<std::string> subs = TomlHelper::ArrayGet<std::vector<std::string>>(root, "nats", i, "subs");
			mNatsClients[name] = mLoop->resource<uvw::nats_client>(this->app_type(), this->app_index());
			std::shared_ptr<uvw::nats_client> client = mNatsClients[name];
			if (host.length() && port > 0) {
				mNatsClients[name]->connect(host, port, true);
				mNatsClients[name]->set_pre_subs(subs);
				client->set_name(name);
			}

            mNatsClients[name]->on<uvw::info_event_nats>([this, client,host,port,subs](auto& e, auto& h) {
                this->log(LogLevel::info, "connected:" ,host, ",port:",port);
				this->on_nats_info(client, e.data);
                std::string str = "{\"verbose\":false,\"pedantic\":false,\"tls_required\":false,\"name\":\"\",\"lang\":\"go\",\"version\":\"1.2.2\",\"protocol\":1}";
                client->send_connect_str(str);
                for(auto&it:subs){
                    client->sub(it);
                }
				});
            mNatsClients[name]->set_sub_callback(std::bind(&ServerBase::on_nats_raw_sub, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4,false));
		}
		return true;
	}


	bool ServerBase::add_fs(std::string path)
	{
		return true;
	}

	bool ServerBase::rem_fs(std::string path)
	{
		return true;
	}

	bool ServerBase::run()
	{
        mRunning = true;
		mLoop->run();
		return true;
	}

	bool ServerBase::listen(std::string ip, int port)
	{
		std::clog << "======> listenat:" << ip << ":" << port << std::endl;

		mTcpHander->on<uvw::listen_event>([this](const uvw::listen_event&, uvw::tcp_handle& srv) {
			std::shared_ptr<uvw::tcp_handle> client = srv.parent().resource<uvw::tcp_handle>();

			std::shared_ptr<uvw::Session> clientSession = srv.parent().resource<uvw::Session>(client);
			clientSession->set_tcpmsg_spliter(Message::fast_split);
			this->mSessionUndefined[clientSession->id()] = clientSession;

			clientSession->on<uvw::on_msg_event>([clientSession, this](const uvw::on_msg_event& ev, const auto& hdl) {
				this->on_raw_msg(clientSession, ev.data);
				});
			clientSession->on<uvw::on_close_event>([clientSession, this](const auto&, const auto&) {
				this->on_session_close(clientSession);
				});
			clientSession->read();
			});


		mTcpHander->bind(ip, port);
		return mTcpHander->listen() == 0;
	}

    void ServerBase::stop()
    {
        if(mRunning == false) return;
        mRunning = false;

        for(auto&it:mThreads){
            it->stop();
        }


        // nats
        // session
        // timers
    }

	int  ServerBase::next_thd_idx()
	{
		mIdxLastSet = (mIdxLastSet++) % mThreads.size();
		return mIdxLastSet;
	}

	void ServerBase::on_raw_msg(std::shared_ptr<uvw::Session>session, std::string data)
	{
		Message msg;
		std::string body;
		bool suc = Message::Decode(data, msg.mHeader, body);
		if (!suc) {
			std::clog << __FUNCTION__ << ",Message::Decode ERROR\n";
			session->close();
			return;
		}

		if (mBindMsgs.find(msg.MsgId()) == mBindMsgs.end())
		{
			std::clog << __FUNCTION__ << " ID:" << msg.MsgId() << " not find handler\n";
			return;
		}

		std::shared_ptr<ProtoMsg> ptr = std::shared_ptr<ProtoMsg>(mBindMsgs[msg.MsgId()].msg_default_instance->New());
		msg.SetProtoPtr(ptr);

		bool ret = msg.parser(data);
		if (!ret) {
			std::clog << __FUNCTION__ << ",Message.parser ERROR\n";
			session->close();
			return;
		}

		int idx = calc_session_thd_idx(session, msg);

		WrappedMessage wmsg;
		wmsg.set(session, msg, mBindMsgs[msg.MsgId()].fn_session);
		this->dispatch_th_work(idx, wmsg);
	}


	int ServerBase::calc_session_thd_idx(std::shared_ptr<uvw::Session> session, Message& msg) {
		return -1;
	}
    int ServerBase::calc_nats_thd_idx(std::shared_ptr<uvw::nats_client> cli,int32_t msgid,std::shared_ptr<ProtoMsg> msg)
    {
        return -1;
    }

	void ServerBase::dispatch_th_work(int idx, WrappedMessage& msg)
	{
		if (mThreads.size()) {
			if (idx < 0) {
				mThreads[next_thd_idx()]->push(msg);
			}
			else {
				mThreads[idx % mThreads.size()]->push(msg);
			}

			return;
		}

		// 主循环做了 copy from Thread
		switch (msg.mType) {
		case WrappedMessage::WrappedMessageType::TIMER_TICK:
        {
            ITimerListenerWPtr ptr = msg.mTimerTick->first;
            auto sptr = ptr.lock();
            if(sptr){
                sptr->__on_timer(msg.mTimerTick->second.id, msg.mTimerTick->second.interval,this->mIndex);
            }
		}
		break;

		case WrappedMessage::WrappedMessageType::SESSION_MSG:
		{
			//this->on_msg(msg.mSessionMsg->first,msg.mSessionMsg->second);
			std::get<2>(*msg.mSessionMsg)(std::get<0>(*msg.mSessionMsg), std::get<1>(*msg.mSessionMsg));
		}
		break;

		case WrappedMessage::WrappedMessageType::NATS_MSG:
		{
            this->on_nats_pub(msg.mNatsMsg->first,
				msg.mNatsMsg->second.sub,
				msg.mNatsMsg->second.id,
				msg.mNatsMsg->second.msg,
				msg.mNatsMsg->second.reply_to);
		}
        break;

        case WrappedMessage::WrappedMessageType::NATS_REQUESTPLY:
            msg.mNatsRequestReplyMsg->second.cb(msg.mNatsRequestReplyMsg->first,msg.mNatsRequestReplyMsg->second.msg,msg.mNatsRequestReplyMsg->second.error);
            break;

		default:
			break;
		}
	}

    void ServerBase::on_nats_raw_sub(std::shared_ptr<uvw::nats_client> client, std::string sub, std::string msg, std::string reply_to,bool timeout)
	{
		std::vector<std::string> v = nonstd::string_utils::split_copy(sub, ".");
		int sub_size = v.size();
		if (sub_size >= 4 && v[2] == "id") {
			int32_t id = std::atoll(v[3].c_str());
			if (id == 0) {
				std::clog << "nats.sub:" << sub << " getid error!" << std::endl;
				return;
			}

			if (mBindMsgs.find(id) == mBindMsgs.end())
			{
				std::clog << __FUNCTION__ << " ID:" << id << " not find handler\n";
				return;
			}

			std::shared_ptr<ProtoMsg> protomsg = std::shared_ptr<ProtoMsg>(mBindMsgs[id].msg_default_instance->New());

			bool suc = protomsg->ParseFromString(msg);
			int index = calc_nats_thd_idx(client, id, protomsg);

			WrappedMessage wmsg;
			wmsg.set(client, sub, reply_to, id, protomsg);
			this->dispatch_th_work(index, wmsg);
		}
	}

	void ServerBase::on_nats_pub(std::shared_ptr<uvw::nats_client> client,
		std::string subject,
		int32_t id,
		std::shared_ptr<ProtoMsg> msg,
		std::string replyto)
	{
		//std::clog << __FUNCTION__ << ", need to be implemented by subclass" << std::endl;
        Message msgst;
        msgst.SetProtoPtr(msg).SetNatsSubject(subject).SetNatsReplyto(replyto);
        msgst.SetMsgId(id);

        if(mBindMsgs.find(id) != mBindMsgs.end() && mBindMsgs[id].fn_nats != nullptr){
            mBindMsgs[id].fn_nats(client,msgst);
        }
        else{
            std::clog << "nat sub:" << subject << ",msgid:"<< id << ", handler not found!\n";
        }      
        
    }

    void ServerBase::log(LogLevel ll,std::string str)
    {
        switch (ll) {
        case LogLevel::debug:
            g_Logger->debug(str);
            break;
        case LogLevel::info:
            g_Logger->info(str);break;
        case LogLevel::warn:
            g_Logger->warn(str);
            break;
        case LogLevel::err:
            g_Logger->error(str);
            break;
        case LogLevel::critical:
            g_Logger->critical(str);
            break;
        default:
            g_Logger->info(str);
            break;
        }
    }

    NatsClinetPtr ServerBase:: get_natsc_byname(std::string name)
    {
        std::shared_lock lk( mMutexNatscs);

        if(mNatsClients.find(name) != mNatsClients.end())
            return mNatsClients[name];
        return nullptr;
    }

    void ServerBase::nats_pub(NatsClinetPtr client,std::string subject,int id,ProtoMsg &msg)
    {
        std::string str_msg = msg.SerializeAsString();
        std::string str_enc= Message::Encode(id,str_msg);
        client->pub(subject,str_enc);
    }

    void ServerBase::nats_reqest_reply(NatsClinetPtr client,std::string subject,int id,ProtoMsg &msg,int mstimout,NatsReqReplyCallBack cb)
    {
        std::string str_msg = msg.SerializeAsString();
        std::string str_enc= Message::Encode(id,str_msg);
        std::string subject_wait_reply = client->request_reply(subject
                        ,str_enc,
                        std::bind(&ServerBase::on_nats_reqest_reply,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5)
                        ,std::chrono::microseconds{mstimout});

        auto thd_id = std::this_thread::get_id();
        std::tuple<NatsReqReplyCallBack,std::thread::id,std::chrono::steady_clock::time_point> tp{cb,thd_id,std::chrono::steady_clock::now()};
        std::lock_guard lk(mMutexRequestReply);
        mNats_Request_Reply[subject_wait_reply] = tp;
    }

    void ServerBase::on_nats_reqest_reply(NatsClinetPtr client,std::string subject,std::string payload,std::string reply_to,bool istimout)
    {
        // this is uv main loop
        std::tuple<NatsReqReplyCallBack,std::thread::id,std::chrono::steady_clock::time_point> tp;
        std::thread::id thd_id{0};
        int thd_idx_distpatch = -1;

        {
            std::lock_guard lk(mMutexRequestReply);
            if(mNats_Request_Reply.find(subject) != mNats_Request_Reply.end()){
                tp = mNats_Request_Reply[subject];
                thd_id = std::get<1>(tp);
                mNats_Request_Reply.erase(subject);
            }
        }

        if(std::get<0>(tp) == nullptr){
            this->log(LogLevel::warn,__FUNCTION__ + std::string(": ") + subject + " not found ");
            return;
        }


        for(auto&it:mThreads){
            if(it->get_thd_id() == thd_id){
                thd_idx_distpatch = it->get_index();
                break;
            }
        }

        //--------------------------------------------------------------------------------------------------------------

        Message msg;
        NatsReqReplyCallBack_Error err = NatsReqReplyCallBack_Error::no_error;
        if(istimout)
            err = NatsReqReplyCallBack_Error::time_out;

        if(!istimout)
        {
            std::string body;
            bool suc = Message::Decode(payload,msg.mHeader,body);
            if(suc){
                if (mBindMsgs.find(msg.MsgId()) == mBindMsgs.end())
                {
                    std::clog << __FUNCTION__ << " ID:" << msg.MsgId() << " not find handler\n";
                    err = NatsReqReplyCallBack_Error::parse_err;
                }
                else
                {
                    std::shared_ptr<ProtoMsg> ptr = std::shared_ptr<ProtoMsg>(mBindMsgs[msg.MsgId()].msg_default_instance->New());
                    msg.SetProtoPtr(ptr);
                    thd_idx_distpatch = this->calc_nats_thd_idx(client,msg.MsgId(),ptr);
                }
            }
            else
            {
                err = NatsReqReplyCallBack_Error::parse_err;
            }
        }

        if(thd_id == std::this_thread::get_id() || thd_idx_distpatch == -1){
            std::get<0>(tp)(client,msg,err);
        }else{
            WrappedMessage wmsg;
            wmsg.set(client,std::get<0>(tp),msg,err);
            this->dispatch_th_work(thd_idx_distpatch,wmsg);
        }
    }

} //namespace Base

