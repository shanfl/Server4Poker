#include "gateserver.h"

int main(int argc, char* argv[])
{
	std::shared_ptr<GateServer> gs = std::make_shared<GateServer>();

	bool ret = gs->init(argc, argv);
	gs->run();

	return 0;
}


void GateServer::on_msg_PlayerLoginReq(Base::SessionPtr session, Base::Message& msg)
{
	std::clog << __FUNCTION__ << std::endl;

	auto ptr = msg.GetProtoMsg<Ps::PlayerLoginReq>();
	if (ptr->las() == Ps::LoginAppSdk::NAMEPASSWORD) {
		// 用户名密码


	}



	// 转发给loginserver
	// nats_reqest_reply()

	//nats_pub_to_anyone(Base::ServerType::Login, msg.MsgId(), msg.BackToString());
}
