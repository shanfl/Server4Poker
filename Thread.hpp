#pragma once;
#include <thread>
#include <vector>
#include "MessagePool.h"
#include "Msg.def.h"
#include <mutex>
namespace Base
{   
    class ServerBase;


    class Thread
    {   
    public:    
        Thread(ServerBase*baseserver);
        void push(Message&msg);
        std::vector<Message> get(int maxnum);
        bool get(Message&msg);
        static void on_work(Thread*ptr);
        void msg_loop();
        void on_msg(Message& msg);
    private:
        ServerBase*mServerPtr = nullptr;
        int mIndex;
        std::thread mThd;  

        MessagePool mMsgPool;
        bool mRun = false;
        //std::mutext mMsgPoolMutex;
    };
}   // namespace Base
