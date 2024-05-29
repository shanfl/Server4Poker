#include "centralserver.h"



void CentralServer::on_natspub_RegisterToCentral(Base::NatsClinetPtr nats,Base::Message&msg)
{

}

bool CentralServer::post_init(const toml::Value& root)
{
    add_timer(TIMERID_HEATBEAT,2000,5000);



    return true;
}


void CentralServer::on_timer(int timerid,int delay,int interval)
{
    log(Base::LogLevel::info, "timer:" + std::to_string(timerid));


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
