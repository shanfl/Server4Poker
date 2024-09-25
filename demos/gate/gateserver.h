#include "ServerBase.h"
#include "gen_proto/Client.pb.h"
class GateServer:public Base::ServerBase
{
    BEGIN_MSG_MAP(GateServer,Base::ServerBase)

    END_MSG_MAP()
public:

};
