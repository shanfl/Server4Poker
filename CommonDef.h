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



enum ThreadDispatchMethod
{
    random_thread       = -2,           // 随机线程
    calc_thread         = -1,           // 需要计算
    uv_thread           = 0,            // uv loop 主线程

    tdm_1,tdm_2,tdm_3,tdm_4,tdm_5,tdm_6,tdm_7,tdm_8,tdm_9,tdm_10,tdm_11,tdm_12,tdm_13,tdm_14,tdm_15,tdm_16,
    max_tmd_thread
};


class CommonDef
{
public:
    static std::string ServerType2Name(ServerType st);
};
}


