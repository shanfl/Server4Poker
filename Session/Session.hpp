#pragma once
#include <string>
#include "uvw.hpp"
#include "SessionDef.h"
namespace uvw
{
	struct Session_t {
		void* data;
	};

	struct on_open_event {

	};

    struct on_ping_event{
        std::string     data;
    };

    struct on_pong_event{
        std::string     data;
    };

    // opcode = 8
    struct on_closewill_event{
        std::string     data;
    };

	struct on_close_event {

	};

    struct on_error_event{
        std::string errstr;
        int code;
    };

	struct on_msg_event {
		SocketOpcode    opcode;
		std::string     data;
	};

	class SessionImpl;

    class Session : public uvw::resource<uvw::Session, Session_t,
            on_open_event,
            on_close_event,
            on_msg_event,
            on_error_event,
            on_ping_event,
            on_pong_event,
            on_closewill_event>
	{
		friend class SessionImpl;
	public:
		Session(uvw::loop::token token, std::shared_ptr<uvw::loop> parent);
        Session(uvw::loop::token token, std::shared_ptr<uvw::loop> parent,std::shared_ptr<tcp_handle> accepted_handle);
		~Session();

	public:
        // uri: tcp://127.0.0.1:2222  or  ws://127.0.0.1:2222
		bool connect(std::string uri);
		void close();

        //if session's websocket，used binary-format txt
		void send(std::string data);

        // after connected
        void read();

		//
		bool is_websocket();
		bool is_client_side();

        // if you use it as a websocket client and set it a anthoer key
        void set_ws_serectkey(std::string serect_key);

        // split raw tcpstream
        // need to be implemented by user
        void set_tcpmsg_spliter(std::function<std::string(std::string& data,bool &err)> f);
	private:
		std::shared_ptr<SessionImpl> d;
	};
}// namespace uvw
