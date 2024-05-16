#pragma once
#include <thread>
#include <vector>
#include "MessagePool.h"
#include "Msg.def.h"
#include "WrappedMessage.hpp"
#include <mutex>
namespace Base
{   
    class ServerBase;

    using MsgPool = MessagePool<WrappedMessage>;

    class Thread
    {   
    public:    
        Thread(ServerBase*baseserver,int index);
        void push(WrappedMessage&msg);
        std::vector<WrappedMessage> get(int maxnum);
        bool get(WrappedMessage&msg);
        static void on_work(Thread*ptr);
        void msg_loop();
    private:
        ServerBase*mServerPtr = nullptr;
        int mIndex;
        std::thread mThd;  

        MessagePool<WrappedMessage> mMsgPool;
        bool mRun = false;
        //std::mutext mMsgPoolMutex;
    };
}   // namespace Base
