#include "ServerBase.h"
#include "Thread.hpp"
#include "google/protobuf/descriptor.h"
#include <google/protobuf/descriptor_database.h>


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
                if (startsWith(name, "protocol")) { // 指定命名空间
                    // 约定消息名称中：Req结尾代表请求， Ack结尾代表响应，Ntf结尾代表通知
                    // 则含有指定后缀的消息才会自动加入关联
                    if (hasSuffix(name)) {
                        auto opts = descriptor->options();
                        protocol::MessageID v = opts.GetExtension(protocol::MsgID);
                        registry[v] = descriptor;
                    }
                }
            }
        }
    }
}


namespace Base {

    ServerBase::ServerBase(int argc,char*argv[]):TimerAlloc(this)
    {
        mLoop = uvw::loop::get_default();
        mTcpHander = mLoop->resource<uvw::tcp_handle>();
    }

    void ServerBase::on_timer_tick(int id,int delay,int interval){
        std::clog << __FUNCTION__ << " id:" << id <<",delay:" << delay << ",interval:" << interval << std::endl;
    }

    // 主线程timer
    int  ServerBase::thd_idx_timer(){
        return -1;
    }

    bool ServerBase::post_init()
    {
        return true;
    }

    bool ServerBase::init()
    {
        bool r1 = init_thd();
        bool r2 = init_db();        
        bool r3 = init_module();
        if(r1&&r2&&r3){
            return post_init();
        }
        return false;
    }

    bool ServerBase::init_db()
    {
        return true;
    }

    bool ServerBase::init_thd()
    {
        return true;
    }

    bool ServerBase::init_module()
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
        mTcpHander->bind(ip, 4242);
        return mTcpHander->listen() == 0;
    }

   void ServerBase::on_raw_msg(std::string &data){
        Message msg = Message::Decode(data);
        msg.SetProtoPtr(create_msg_by_id(msg.MsgId())); 
        this->dispatch_work(msg);               
    }

    int ServerBase::dispatch_thd(Message &msg)
    {
        return -1;
    }

    void ServerBase::dispatch_work(Message &msg)
    {
        int thd_index = dispatch_thd(msg);
        if(thd_index < 0){
            mThreads[random()%mThreads.size()]->push(msg);
        }else{
            mThreads[thd_index%mThreads.size()]->push(msg);
        }
    }


    std::shared_ptr<ProtoMsg> ServerBase::create_msg_by_id(uint32_t msgid)
    {
        return nullptr;
    }

} //namespace Base

