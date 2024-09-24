#include "user.h"

bool UserServer::post_init(const toml::Value& root)
{
    //add_timer(TIMERID_HEATBEAT,2000,2000);
    return true;
}


void UserServer::on_timer(int timerid,int interval)
{
    log(Base::LogLevel::info, "timer:" + std::to_string(timerid));
}


void UserServer::on_natspub_PlayerLoginReq(Base::NatsClinetPtr natsc,Base::Message&msg)
{
    std::shared_ptr<Pb::Client::PlayerLoginReq> msgptr = msg.GetProtoMsg<Pb::Client::PlayerLoginReq>();
    if(!msgptr) return;

    Pb::Client::LoginAppSdk loginWay = msgptr->las();

    ResultCode loginResult;

    int64_t uid = msgptr->id();
    if(uid > 0)
    {
        loginResult = Login_ByID(uid);
    }
    else
    {
        uid = 0;
        if(loginWay == NAMEPASSWORD){
            // 如果uid > 0 但是 loginResult < 0 说明登录错误
            // 如果uid == 0 说明可以注册
            loginResult = Login_ByNamePass(uid,msgptr->name(),msgptr->pass());
        }else if(loginWay == GUEST){
            //loginResult = error_rc;
        }
        else if(WECHAT == loginWay){
            //loginResult = error_rc;
        }
    }

    if(loginResult == error_rc){
        // 登录失败

        //send-login-failed

        return;
    }

    //---------------------------------------------------------------------------------
    if(uid == 0 && loginResult == user_not_exists_rc){
        // 注册新用户

    }


    //---------------------------------------------------------------------------------
    // 获取user的info

}


ResultCode UserServer::Login_ByID(int64_t &uid)
{

}

ResultCode UserServer::Login_ByNamePass(int64_t &uid,std::string name,std::string pass)
{

}

int main(int argc,char*argv[])
{
    auto  gs = std::make_shared<UserServer>();

    bool ret =  gs->init(argc,argv);
    if(!ret){
        std::clog << "CentralServer init error \n";
        return 1;
    }

    gs->run();

    return 0;
}
