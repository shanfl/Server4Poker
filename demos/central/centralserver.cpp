#include "centralserver.h"



void CentralServer::on_natspub_RegisterToCentral(Base::NatsClinetPtr nats,Base::Message&msg)
{

}

bool CentralServer::post_init(const toml::Value& root)
{
    add_timer(TIMERID_HEATBEAT,2000,2000);

    for(int i = 0;i < 10;i++){
        auto tm = std::make_shared<Timer123>();
        tm->init(this);
        tm->add_timer(1+i,1000,4000 + i * 1000);
        mTimers.push_back(tm);
    }

    return true;
}


void CentralServer::on_timer(int timerid,int delay,int interval)
{
    log(Base::LogLevel::info, "timer:" + std::to_string(timerid));
    static int i = 0;
    i++;

    if(i % 36 == 0 && mTimers.size()){
        log(Base::LogLevel::info,"=========> remove one ");
        mTimers.erase(mTimers.begin());
    }
}


int main(int argc,char*argv[])
{
    CentralServer gs;

    bool ret =  gs.init(argc,argv);
    if(!ret){
        std::clog << "CentralServer init error \n";
        return 1;
    }

    gs.run();

    return 0;
}
