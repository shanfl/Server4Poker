#include "Session/Session.hpp"
#include "uvw.hpp"
#include <iostream>

void login()
{

}


int main(){

    auto loop = uvw::loop::get_default();

    auto session = loop->resource<uvw::Session>();

    session->on<uvw::on_open_event>([](auto&e,auto&h){
        std::clog << "on_open_event" << std::endl;
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
