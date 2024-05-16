#pragma once;
#include <thread>
#include <vector>
#include "MessagePool.h"
#include "Msg.def.h"
#include "WrappedMessageBuilder.hpp"
#include <mutex>
namespace Base
{   
    class ServerBase;

    using MsgPool = MessagePool<WrappedMessageBuilder>;

    class Thread
    {   
    public:    
        Thread(ServerBase*baseserver,int index);
        void push(WrappedMessageBuilder&msg);
        std::vector<WrappedMessageBuilder> get(int maxnum);
        bool get(WrappedMessageBuilder&msg);
        static void on_work(Thread*ptr);
        void msg_loop();
        void on_msg(WrappedMessageBuilder& msg);
    private:
        ServerBase*mServerPtr = nullptr;
        int mIndex;
        std::thread mThd;  

        MessagePool<WrappedMessageBuilder> mMsgPool;
        bool mRun = false;
        //std::mutext mMsgPoolMutex;
    };
}   // namespace Base
