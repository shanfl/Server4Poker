#include "ServerBase.h"
#include <map>
#include "gen_proto/Central.pb.h"

#define TIMERID_HEATBEAT (Base::MIN_USER_TIMERID + 1)

struct ServerInfo
{
    int32_t server_type;
    int32_t server_index;
    std::chrono::steady_clock::time_point last_active;
};

using ServerLayout = std::map<std::pair<int32_t,int32_t> ,ServerInfo> ;

class CentralServer:public Base::ServerBase
{
    BEGIN_MSG_MAP(CentralServer,Base::ServerBase)
    BIND_NATS_MSG(Pb::Central,ID_RegisterToCentral,RegisterToCentral)
    END_MSG_MAP()

    virtual bool post_init(const toml::Value& root) override;

    virtual void on_timer(int timerid,int delay,int interval) override;
public:
    void on_natspub_RegisterToCentral(Base::NatsClinetPtr nats,Base::Message&msg);
public:
    ServerLayout mServerLayout;
};
