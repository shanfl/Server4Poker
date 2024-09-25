#include "ServerBase.h"
#include "gen_proto/Client.pb.h"
class GateServer:public Base::ServerBase
{
    BEGIN_MSG_MAP(GateServer,Base::ServerBase)
    BIND_SESSION_MSG(Ps,ID_PlayerLoginReq,PlayerLoginReq)
    END_MSG_MAP()


public:
    void on_msg_PlayerLoginReq(Base::SessionPtr session, Base::Message& msg);
};
