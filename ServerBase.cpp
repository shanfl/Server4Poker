#include "ServerBase.h"
#include "WrappedMessage.hpp"
#include <filesystem>
#include "Thread.hpp"
#include "OptionParser.h"
#include "google/protobuf/descriptor.h"
#include <google/protobuf/descriptor_database.h>
#include "TomlHelper.h"
#include "3rd/string-utils/string_utils.h"

#if 0
static std::unordered_map<uint32_t, const google::protobuf::Descriptor*> g_registry;

void initProtoRegistryV2()
{
    using namespace google::protobuf;
    const DescriptorPool* pool = DescriptorPool::generated_pool();
    DescriptorDatabase* db = pool->internal_generated_database();
    if (db == nullptr) {
        return;
    }
    std::vector<std::string> file_names;
    db->FindAllFileNames(&file_names);   // 遍历得到所有proto文件名
    for (const std::string& filename : file_names)
    {
        const FileDescriptor* fileDescriptor = pool->FindFileByName(filename);
        if (fileDescriptor == nullptr)
        {
            continue;
        }
        int msgcount = fileDescriptor->message_type_count();
        for (int i = 0; i < msgcount; i++)
        {
            const Descriptor* descriptor = fileDescriptor->message_type(i);
            if (descriptor != nullptr)
            {
                const std::string& name = descriptor->full_name();
#if 0
                if (startsWith(name, "protocol")) { // 指定命名空间
                    // 约定消息名称中：Req结尾代表请求， Ack结尾代表响应，Ntf结尾代表通知
                    // 则含有指定后缀的消息才会自动加入关联
                    if (hasSuffix(name)) {
                        auto opts = descriptor->options();
                        protocol::MessageID v = opts.GetExtension(protocol::MsgID);
                        registry[v] = descriptor;
                    }
                }
#endif
            }
        }
    }
}
#endif


namespace Base {

    ServerBase::ServerBase():TimerAlloc(this)
    {
        mLoop = uvw::loop::get_default();
        mTcpHander = mLoop->resource<uvw::tcp_handle>();
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

    void ServerBase::on_timer_tick(int id,int delay,int interval){
        std::clog << __FUNCTION__ << " id:" << id <<",delay:" << delay << ",interval:" << interval << std::endl;
    }

    bool ServerBase::post_init(const toml::Value& root)
    {
        return true;
    }

    bool ServerBase::init(int argc,char*argv[])
    {
        //get app path
        std::string path = std::string(argv[0]);
        std::filesystem::path p(path);
        mAppPath = p.parent_path().string();

        //-l abc.log -c int.cfg
        using optparse::OptionParser;
        OptionParser parser = OptionParser().description("==core==");
        parser.add_option("-l", "--log").dest("log")
            .help("write  log").metavar("LOG");

        parser.add_option("-tc", "--toml").dest("toml")
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

        std::string fullpath = app_path() + "/" + mTomlCfg;
        std::ifstream ifs(fullpath);
        toml::ParseResult pr = toml::parse(ifs);
        if(!pr.valid()) {
            std::clog << "parser toml:" << mTomlCfg << "failed \n";
            return false;
        }

        this->mName = TomlHelper::TGet<std::string>(pr.value,"","name","unknown");
        this->mType = TomlHelper::TGet<int>(pr.value,"","type",0);
        this->mIndex = TomlHelper::TGet<int>(pr.value,"","index",0);

        bool r1 = init_thd(pr.value);
        bool r2 = init_db(pr.value);
        bool r3 = init_module(pr.value);
        bool r4 = init_serve(pr.value);
        if(r1&&r2&&r3 && r4){
            return post_init(pr.value);
        }
        return false;
    }

     bool ServerBase::init_serve(const toml::Value& root)
     {
        std::string ip = TomlHelper::TGet<std::string>(root,"server","ip","0.0.0.0");
        int port = TomlHelper::TGet<int>(root,"server","port",8989);

        return listen(ip,port);
     }

    bool ServerBase::init_db(const toml::Value& root)
    {
        return true;
    }

    bool ServerBase::init_thd(const toml::Value& root)
    {
        int ntd = std::thread::hardware_concurrency();
        int cnt_thread = TomlHelper::TGet<int>(root,"thread","cnt",ntd);
        if(cnt_thread < 0 || cnt_thread > ntd)
            cnt_thread = ntd;

        for(int i = 0;i < cnt_thread;i++)
            mThreads.emplace_back(std::make_shared<Thread>(this,i));

        return true;
    }

    bool ServerBase::init_module(const toml::Value& root)
    {
        return true;
    }

    bool ServerBase::init_nats(const toml::Value& root)
    {
        int n = TomlHelper::ArrayGetCnt(root,"nats");
        for(int i = 0;i < n;i++){
            std::string name = TomlHelper::ArrayGet<std::string>(root,"nats",i,"name",std::to_string(i));
            name += "." + std::to_string(i);
            std::string host = TomlHelper::ArrayGet<std::string>(root,"nats",i,"host","");
            int port =  TomlHelper::ArrayGet<int>(root,"nats",i,"port",0);
            std::vector<std::string> subs = TomlHelper::ArrayGet<std::vector<std::string>>(root,"nats",i,"subs");
            mNatsClients[name] = mLoop->resource<uvw::nats_client>(this->app_type(),this->app_index());
            std::shared_ptr<uvw::nats_client> client = mNatsClients[name];
            if(host.length() && port > 0){
                mNatsClients[name]->connect(host,port,true);
                mNatsClients[name]->set_pre_subs(subs);
                client->set_name(name);
            }

            mNatsClients[name]->on<uvw::info_event_nats>([this,client](auto&e,auto&h){
                this->on_nats_info(client,e.data);
            });
            mNatsClients[name]->set_sub_callback(std::bind(&ServerBase::on_nats_raw_sub,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4));
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
        mLoop->run();
        return true;
    }
    
    bool ServerBase::listen(std::string ip,int port)
    {
        std::clog << "======> listenat:" << ip << ":" << port << std::endl;

        mTcpHander->on<uvw::listen_event>([this](const uvw::listen_event&, uvw::tcp_handle& srv) {
            std::shared_ptr<uvw::tcp_handle> client = srv.parent().resource<uvw::tcp_handle>();

            std::shared_ptr<uvw::Session> clientSession = srv.parent().resource<uvw::Session>(client);
            clientSession->set_tcpmsg_spliter(Message::fast_split);
            this->mSessionUndefined[clientSession->id()] = clientSession;

            clientSession->on<uvw::on_msg_event>([clientSession,this](const uvw::on_msg_event& ev, const auto& hdl) {
                //std::clog << "msg:" << ev.data << ",opcode:" << ev.opcode << "\n";
                //clientSession->send(ev.data);
                this->on_raw_msg(clientSession,ev.data);
                });
            clientSession->on<uvw::on_close_event>([clientSession,this](const auto&,const auto&){
                this->on_session_close(clientSession);
            });
            clientSession->read();
        });


        mTcpHander->bind(ip, port);
        return mTcpHander->listen() == 0;
    }

    int  ServerBase::next_thd_idx()
    {
        mIdxLastSet = (mIdxLastSet++)%mThreads.size();
        return mIdxLastSet;
    }
    
#if 0
    void ServerBase::on_raw_msg(std::shared_ptr<uvw::Session>session, std::string data)
    {
        Message msg;
        std::string body;
        bool suc = Message::Decode(data,msg.mHeader,body);
        if(!suc){
            std::clog << __FUNCTION__ << ",Message::Decode ERROR\n";
            session->close();
            return;
        }

        msg.SetProtoPtr(create_msg_by_id(msg.MsgId()));
        bool ret = msg.parser(data);
        if(!ret){
            std::clog << __FUNCTION__ << ",Message.parser ERROR\n";
            session->close();
            return;
        }

        int idx = calc_session_thd_idx(session,msg);

        WrappedMessage wmsg;
        wmsg.set(session,msg);
        this->dispatch_th_work(idx,wmsg);
    }
#endif

    void ServerBase::on_raw_msg(std::shared_ptr<uvw::Session>session, std::string data)
    {
        Message msg;
        std::string body;
        bool suc = Message::Decode(data,msg.mHeader,body);
        if(!suc){
            std::clog << __FUNCTION__ << ",Message::Decode ERROR\n";
            session->close();
            return;
        }

        if(mBindMsgs.find(msg.MsgId()) == mBindMsgs.end())
        {
            std::clog << __FUNCTION__ << " ID:" << msg.MsgId() << " not find handler\n";
            return;
        }

        std::shared_ptr<ProtoMsg> ptr = std::shared_ptr<ProtoMsg>(mBindMsgs[msg.MsgId()].msg_default_instance->New());
        msg.SetProtoPtr(ptr);

        bool ret = msg.parser(data);
        if(!ret){
            std::clog << __FUNCTION__ << ",Message.parser ERROR\n";
            session->close();
            return;
        }

        int idx = calc_session_thd_idx(session,msg);

        WrappedMessage wmsg;
        wmsg.set(session,msg,mBindMsgs[msg.MsgId()].fn_session);
        this->dispatch_th_work(idx,wmsg);
    }
    

    int ServerBase::calc_session_thd_idx(std::shared_ptr<uvw::Session> session,Message&msg){
        return -1;
    }

    int ServerBase::calc_nats_thd_idx(std::shared_ptr<uvw::nats_client> cli,int32_t msgid,std::shared_ptr<ProtoMsg> msg)
    {
        return -1;
    }

     void ServerBase::dispatch_th_work(int idx,WrappedMessage &msg)
     {
         if(mThreads.size()){
             if(idx < 0){
                 mThreads[next_thd_idx()]->push(msg);
             }else{
                 mThreads[idx%mThreads.size()]->push(msg);
             }

             return;
         }

         // 主循环做了 copy from Thread
         switch (msg.mType) {
             case WrappedMessage::WrappedMessageType::TIMER_TICK:
             {
                 std::shared_ptr<TimerAlloc> ptr =  msg.mTimerTick->first.lock();
                 if(ptr)
                     ptr->on_timer_tick(msg.mTimerTick->second.id,msg.mTimerTick->second.delay,msg.mTimerTick->second.interval);
             }
             break;
             case WrappedMessage::WrappedMessageType::SESSION_MSG:
             {
                 //this->on_msg(msg.mSessionMsg->first,msg.mSessionMsg->second);
                 std::get<2>(*msg.mSessionMsg)(std::get<0>(*msg.mSessionMsg),std::get<1>(*msg.mSessionMsg));
             }
             case WrappedMessage::WrappedMessageType::NATS_MSG:
                break;

             default:
                 break;
         }
     }

     void ServerBase::on_nats_raw_sub(std::shared_ptr<uvw::nats_client> client,std::string sub,std::string msg,std::string reply_to)
     {
         std::vector<std::string> v = nonstd::string_utils::split_copy(sub,".");
         int sub_size = v.size();
         if(sub_size >= 4 && v[2] == "id"){
             int32_t id = std::atoll(v[3].c_str());
             if(id == 0){
                 std::clog << "nats.sub:" << sub << " getid error!" << std::endl;
                 return;
             }

             if(mBindMsgs.find(id) == mBindMsgs.end())
             {
                 std::clog << __FUNCTION__ << " ID:" << id << " not find handler\n";
                 return;
             }

             std::shared_ptr<ProtoMsg> protomsg = std::shared_ptr<ProtoMsg>(mBindMsgs[id].msg_default_instance->New());

             bool suc = protomsg->ParseFromString(msg);
             int index = calc_nats_thd_idx(client,id,protomsg);

             WrappedMessage wmsg;
             wmsg.set(client,sub,reply_to,id,protomsg);
             this->dispatch_th_work(index,wmsg);
         }
     }

} //namespace Base

