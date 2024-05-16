#include "Session.hpp"
#include "SessionImpl.hpp"
#include <iostream>
namespace uvw {

    Session::Session(uvw::loop::token token, std::shared_ptr<uvw::loop> parent) : uvw::resource<uvw::Session, Session_t, on_open_event, on_close_event, on_msg_event,on_error_event,on_ping_event,on_pong_event,on_closewill_event>(token, parent)
	{
		d = std::make_shared<SessionImpl>(this, parent);
	}

    Session::Session(uvw::loop::token token, std::shared_ptr<uvw::loop> parent,std::shared_ptr<tcp_handle> accepted_handle): uvw::resource<uvw::Session, Session_t, on_open_event, on_close_event, on_msg_event,on_error_event,on_ping_event,on_pong_event,on_closewill_event>(token, parent)
    {
        d = std::make_shared<SessionImpl>(this, parent);
        d->on_tcp_connected(SideClient::REMOTE_CLIENT,accepted_handle);
    }

	//Session::Session(std::shared_ptr<uvw::loop> loop,std::shared_ptr<uvw::tcp_handle>&tcphandle)
	//{
	//    d = std::make_shared<SessionImpl>(this,loop,tcphandle);
	//}

	Session::~Session() {
		std::clog << __FUNCTION__ << std::endl;
        close();
	}

    int64_t Session::id()
    {
        return d->id();
    }

	bool Session::connect(std::string uri)
	{
		d->connect(uri);
		return true;
	}

	void Session::read()
	{
		d->read();
	}

	void Session::close()
	{
        d->close();
	}

	void Session::send(std::string data)
	{
		d->send(data);
	}

	bool Session::is_websocket()
	{
        d->is_websocket();
	}

	//bool Session::is_client()
	//{
	//    return  false;
	//}

    void Session::set_ws_serectkey(std::string serect_key)
    {
        d->set_ws_serectkey(serect_key);
    }

    void Session::set_tcpmsg_spliter(std::function<std::string(std::string& data,bool &err)> f)
    {
        d->set_tcpmsg_spliter(f);
    }

}  // namespace uvw
