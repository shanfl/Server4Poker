#include "centralserver.h"



void CentralServer::on_natspub_RegisterToCentral(Base::NatsClinetPtr nats,Base::Message&msg)
{

}

bool CentralServer::post_init(const toml::Value& root)
{
    add_timer(TIMERID_HEATBEAT,2000,1300);

    for(int i = 0;i < 0;i++){
        auto tm = std::make_shared<Timer123>(this);
        //tm->init(this);
        tm->add_timer(1+i,300,1000 + i * 10);
        mTimers.push_back(tm);
    }

    return true;
}


void CentralServer::on_timer(int timerid,int interval)
{
    log(Base::LogLevel::info, "timer:" + std::to_string(timerid));
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
