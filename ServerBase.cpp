#include "ServerBase.h"
#include <filesystem>
#include "Thread.hpp"
#include "OptionParser.h"
#include "google/protobuf/descriptor.h"
#include <google/protobuf/descriptor_database.h>
#include "toml/TomlHelper.h"

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
        if(cnt_thread == -1 || cnt_thread > ntd)
            cnt_thread = ntd;
        if(cnt_thread == 0)
            cnt_thread= 1;

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
        mTcpHander->bind(ip, 4242);
        return mTcpHander->listen() == 0;
    }

   void ServerBase::on_raw_msg(std::shared_ptr<uvw::Session>session, std::string &data){
        Message msg = Message::Decode(data);
        msg.SetProtoPtr(create_msg_by_id(msg.MsgId()));
        //TODO: parser

        WrappedMessage wmsg;
        wmsg.set(session,msg);
        this->dispatch_work(wmsg);
    }

    int ServerBase::calc_thd_idx(WrappedMessage &msg)
    {
        return -1;
    }

    void ServerBase::dispatch_work(WrappedMessage &msg)
    {
        int thd_index = calc_thd_idx(msg);
        this->dispatch_th_work(thd_index,msg);
    }

     void ServerBase::dispatch_th_work(int idx,WrappedMessage &msg)
     {
         if(idx < 0){
             mThreads[random()%mThreads.size()]->push(msg);
         }else{
             mThreads[idx%mThreads.size()]->push(msg);
         }
     }

    std::shared_ptr<ProtoMsg> ServerBase::create_msg_by_id(uint32_t msgid)
    {
        return nullptr;
    }

} //namespace Base

