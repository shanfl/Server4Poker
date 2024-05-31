#include "login.h"

bool LoginServer::post_init(const toml::Value& root)
{
    //add_timer(TIMERID_HEATBEAT,2000,2000);
    return true;
}


void LoginServer::on_timer(int timerid,int interval)
{
    log(Base::LogLevel::info, "timer:" + std::to_string(timerid));
}


int main(int argc,char*argv[])
{
    auto  gs = std::make_shared<LoginServer>();

    bool ret =  gs->init(argc,argv);
    if(!ret){
        std::clog << "CentralServer init error \n";
        return 1;
    }

    gs->run();

    return 0;
}
