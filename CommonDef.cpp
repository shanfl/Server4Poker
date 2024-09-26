#include "CommonDef.h"

namespace Base
{
    std::string CommonDef::ServerType2Name(ServerType st)
    {
        switch (st)
        {

        case ServerType::Central:
            return "central";
        case ServerType::Gate:
            return "gate";
        case ServerType::PlanServer:
            return "plan";
        case ServerType::Ddz:
            return "ddz";
        case ServerType::UnKnown:
        default:
            return "unknown";
            break;
        }
    }

    int CommonDef::Name2ServerType(std::string name)
    {
        if(name == "central")       return (int)ServerType::Central;
        else if(name == "gate")     return (int)ServerType::Gate;
        else if(name == "login")    return (int)ServerType::Login;
        else if(name == "user")     return (int)ServerType::User;
        else                        return (int)ServerType::UnKnown;
    }
}
