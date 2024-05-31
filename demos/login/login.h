#include "ServerBase.h"
#include <map>
#include "gen_proto/Central.pb.h"


class LoginServer:public Base::ServerBase
{
    BEGIN_MSG_MAP(LoginServer,Base::ServerBase)
    //BIND_NATS_MSG(Pb::Central,ID_RegisterToCentral,RegisterToCentral)
    END_MSG_MAP()

    virtual bool post_init(const toml::Value& root) override;

    virtual void on_timer(int timerid,int interval) override;
};
