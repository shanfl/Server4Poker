#pragma once
#include <string>
#include <inttypes.h>

namespace Base
{
enum class ServerType : int16_t
{
    Server_UnKnown = 0,         // 未知
    Server_Central = 1,         
    Server_Gate = 2,
    Server_PlanServer = 3,
    Server_Ddz = 4,
};

struct ServerId
{
    int16_t servertype;
    int16_t serverindex;
};

class CommonDef
{
public:
    static std::string ServerType2Name(ServerType st);
};
}


