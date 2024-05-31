#include "ServerBase.h"
#include <map>
#include "gen_proto/Client.pb.h"

using namespace Base;
using namespace Pb::Client;
class LoginServer:public Base::ServerBase
{
public:
    DECLARE_SERVER_TYPE(Base::ServerType::Server_Login)

    BEGIN_MSG_MAP(LoginServer,Base::ServerBase)
    BIND_NATS_MSG(Pb::Client,ID_PlayerLoginReq,PlayerLoginReq)
    END_MSG_MAP()

    virtual bool post_init(const toml::Value& root) override;

    virtual void on_timer(int timerid,int interval) override;
protected:
    void on_natspub_PlayerLoginReq(Base::NatsClinetPtr natsc,Base::Message&msg);
};
