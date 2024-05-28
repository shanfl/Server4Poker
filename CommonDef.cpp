#include "CommonDef.h"

namespace Base
{
    std::string CommonDef::ServerType2Name(ServerType st)
    {
        switch (st)
        {

        case ServerType::Server_Central:
            return "central";
        case ServerType::Server_Gate:
            return "gate";
        case ServerType::Server_PlanServer:
            return "plan";
        case ServerType::Server_Ddz:
            return "ddz";
        case ServerType::Server_UnKnown:   
        default:
            return "unknown";
            break;
        }
    }
}