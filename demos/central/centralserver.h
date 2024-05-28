#include "ServerBase.h"


struct ServerInfo
{
    int32_t servertype;
    int32_t serverindex;
    std::vector<int32_t>indexs;
}

using std::map<std::pair<int32_t,int32_t> ,ServerInfo> ServerLayout;

class CentralServer:public Base::ServerBase
{
    BEGIN_MSG_MAP(CentralServer,Base::ServerBase)
    END_MSG_MAP()
public:
    ServerLayout mServerLayout;
};
