#include "Session/Session.hpp"
#include "uvw.hpp"
#include <iostream>
#include "gen_proto/Client.pb.h"
#include "gen_proto/Core.pb.h"
#include "Msg.def.h"
void req_login(const std::shared_ptr<uvw::Session>&session)
{
    Ps::PlayerLoginReq req;
    req.set_osplatform(Ps::OS_PLATFORM::OS_UNKNOWN);
    req.set_las(Ps::LoginAppSdk::NAMEPASSWORD);
    req.set_id(0);
    req.set_name("guest001");
    req.set_pass("pass001");
    //req.app_spec("");

    std::string str = Base::Message::EncodeWs(Ps::ID_PlayerLoginReq,req.SerializeAsString());
    session->send(str);
}


int main(){

    auto loop = uvw::loop::get_default();

    auto session = loop->resource<uvw::Session>();

    session->on<uvw::on_open_event>([session](auto&e,auto&h){
        std::clog << "on_open_event" << std::endl;
        req_login(session);
    });

    session->on<uvw::on_close_event>([](auto&e,auto&h){
        std::clog << "on_close_event" << std::endl;
    });

    session->on<uvw::on_msg_event>([](auto&e,auto&h){
        std::clog << "on_msg_event" << std::endl;
    });



    session->connect("ws://127.0.0.1:8899");

    loop->run();

    std::clog << "end!" << std::endl;
    return 0;

};
