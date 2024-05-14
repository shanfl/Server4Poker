#include "ServerBase.h"
#include "Thread.hpp"
namespace Base{
    Thread::Thread(ServerBase*baseserver,int idx): mServerPtr(baseserver),mIndex(idx)
    {
        mRun = true;
        mThd = std::thread(Thread::on_work,this);    
    }
    
    void Thread::push(Message&msg)
    {
        mMsgPool.push(msg);
    }

    std::vector<Message> Thread::get(int maxnum)
    {
        return mMsgPool.get(maxnum);
    }

    void Thread::on_work(Thread*ptr)
    {
        ptr->msg_loop();
    }

    void Thread::on_msg(Message& msg)
    {

    }

    void Thread::msg_loop(){
        while(mRun){
            Message msg;
            bool b = get(msg);
            if(!b)
            {
                std::this_thread::sleep_for(std::chrono::microseconds(10));
                return;
            }
            mServerPtr->on_msg(msg);
        }
    }
}
