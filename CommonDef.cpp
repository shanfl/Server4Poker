#include "CommonDef.h"

namespace Base
{
    std::string CommDef::ServerType2Name(ServerType st)
    {
        switch (st)
        {

        case Server_Central:
            return "central";
        case Server_Gate:
            return "gate";
        case Server_PlanServer:
            return "plan";
        case Server_Ddz:
            return "ddz";
        case Server_UnKnown:   
        default:
            return "unknown";
            break;
        }
    }
}