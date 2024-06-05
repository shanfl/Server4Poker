#include "ServerBase.h"
#include <map>
#include "gen_proto/Client.pb.h"

using namespace Base;
using namespace Pb::Client;

enum class ResultCode : int8_t
{
    success_rc = 0,          // 成功
    error_rc,                // 错误
    user_not_exists_rc,      // 用户不存在
};

class UserServer:public Base::ServerBase
{
public:
    DECLARE_SERVER_TYPE(Base::ServerType::Server_User)

    BEGIN_MSG_MAP(UserServer,Base::ServerBase)
    BIND_NATS_MSG(Pb::Client,ID_PlayerLoginReq,PlayerLoginReq)
    END_MSG_MAP()

    virtual bool post_init(const toml::Value& root) override;

    virtual void on_timer(int timerid,int interval) override;
protected:
    void on_natspub_PlayerLoginReq(Base::NatsClinetPtr natsc,Base::Message&msg);

    ResultCode Login_ByID(int64_t &uid);
    ResultCode Login_ByNamePass(int64_t &uid,std::string name,std::string pass);
};
