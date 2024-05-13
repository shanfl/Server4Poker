#pragma once;
#include <thread>
#include <vector>
#include "MessagePool.h"
#include "Msg.def.h"
namespace Base
{   
    class ServerBase;


    class Thread
    {   
    public:
    
        Thread(ServerBase*baseserver);
        void Push();
        void std::vector<Message> Get(int maxnum);
        static void on_work(Thread*ptr);
        void msg_loop();
        void on_msg(Message& msg);
    private:
        int mIndex;
        std::thread mThd;  
    };
}   // namespace Base
