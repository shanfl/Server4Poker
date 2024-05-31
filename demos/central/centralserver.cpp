#include "centralserver.h"

void CentralServer::on_natspub_RegisterToCentral(Base::NatsClinetPtr nats,Base::Message&msg)
{
    std::shared_ptr<Pb::Central::RegisterToCentral> msgptr = msg.GetProtoMsg<Pb::Central::RegisterToCentral>();
    if(!msgptr) return;

    int sindex  = msgptr->serverindex();
    int stype   = msgptr->servertype();
    std::string sname = msgptr->servername();

    {
        std::lock_guard lk(mMutexServerLayout);
        mServerLayout[std::pair(stype,sindex)] = {sname,stype,sindex,std::chrono::steady_clock::now()};
    }

    pub_ServerInfo(nats);
}

void CentralServer::pub_ServerInfo(Base::NatsClinetPtr natsc)
{
    if(natsc == nullptr){
        natsc = get_natsc_byname("system");
        if(!natsc) return;
    }

    Pb::Central::CentralHeartBeat chb;
    {
        std::shared_lock lk(mMutexServerLayout);
        for(auto&it:mServerLayout)
        {
            Pb::Central::RegisterToCentral *item = chb.add_natsclients();
            item->set_servername(it.second.server_name);
            item->set_serverindex(it.first.second);
            item->set_servertype(it.first.first);
        }
    }

    this->nats_pub(natsc,subject_byid(Pb::Central::MsgID::ID_CentralHeartBeat),Pb::Central::MsgID::ID_CentralHeartBeat,chb);
}

bool CentralServer::post_init(const toml::Value& root)
{
    add_timer(TIMERID_HEATBEAT,2000,2000);


#if 0
    for(int i = 0;i < 0;i++){
        auto tm = std::make_shared<Timer123>(this);
        //tm->init(this);
        tm->add_timer(1+i,300,1000 + i * 10);
        mTimers.push_back(tm);
    }
#endif


    return true;
}


void CentralServer::on_timer(int timerid,int interval)
{
    log(Base::LogLevel::info, "timer:" + std::to_string(timerid));

    // 检查超时的natsclient 并去掉
    pub_ServerInfo(nullptr);


#if 0



    static int i = 0;
    i++;

//    if(i % 20 == 0 && mTimers.size()){
//        log(Base::LogLevel::info,"=========> remove one ");
//        mTimers.erase(mTimers.begin());

//        for(int j = 0;j < 1;j++){
//            auto tm = std::make_shared<Timer123>();
//            tm->init(this);
//            tm->add_timer(1+i,1000,1000 + j * 10);
//            mTimers.push_back(tm);
//        }
//    }

        if(i % 37 == 0 && mTimers.size()){
            log(Base::LogLevel::info,"=========> remove one ");
            mTimers.clear();
            for(int k = i;k < i+0;k++){
                auto tm = std::make_shared<Timer123>(this);
                tm->add_timer(1+k,300,1000 + random()%4 * 10);
                mTimers.push_back(tm);
            }
        }
#endif
}


int main(int argc,char*argv[])
{
    auto  gs = std::make_shared<CentralServer>();

    bool ret =  gs->init(argc,argv);
    if(!ret){
        std::clog << "CentralServer init error \n";
        return 1;
    }

    gs->run();

    return 0;
}
