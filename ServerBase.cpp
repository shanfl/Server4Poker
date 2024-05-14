#include "ServerBase.h"
#include "Thread.hpp"
namespace Base {



    int ServerBase::dispatch_thd(Message &msg)
    {
        return -1;
    }

    void ServerBase::dispatch_work(Message &msg)
    {
        int thd_index = dispatch_thd(msg);
        if(thd_index == -1){
            mThreads[random()%mThreads.size()]->push(msg);
        }else{
            mThreads[thd_index%mThreads.size()]->push(msg);
        }
    }
} //namespace Base

