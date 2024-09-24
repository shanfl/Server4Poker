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


void LoginServer::on_natspub_PlayerLoginReq(Base::NatsClinetPtr natsc,Base::Message&msg)
{
    std::shared_ptr<Pb::Client::PlayerLoginReq> msgptr = msg.GetProtoMsg<Pb::Client::PlayerLoginReq>();
    if(!msgptr) return;

    LoginAppSdk wayLogin = msgptr->las();
    switch (wayLogin) {
    //case IDANDPASSWORD:
    {
        //this->nats_reqest_reply() // to user-server
    }
    break;
    }
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
