#include "ServerBase.h"
#include "Thread.hpp"
namespace Base{
    Thread::Thread(ServerBase*baseserver,int idx): mServerPtr(baseserver),mIndex(idx)
    {
        mRun = true;
        mThd = std::thread(Thread::on_work,this);    
    }
    
    void Thread::push(WrappedMessage&msg)
    {
        mMsgPool.push(msg);
    }

    std::vector<WrappedMessage> Thread::get(int maxnum)
    {
        return mMsgPool.get(maxnum);
    }

    void Thread::on_work(Thread*ptr)
    {
        ptr->msg_loop();
    }

    void Thread::msg_loop(){
        while(mRun){
            WrappedMessage msg;
            bool b = get(msg);
            if(!b)
            {
                std::this_thread::sleep_for(std::chrono::microseconds(10));
                continue;
            }

            switch (msg.mType) {
                case WrappedMessage::WrappedMessageType::TIMER_TICK:
                {
                    std::shared_ptr<TimerAlloc> ptr =  msg.mTimerTick->first.lock();
                    if(ptr)
                        ptr->on_timer_tick(msg.mTimerTick->second.id,msg.mTimerTick->second.delay,msg.mTimerTick->second.interval);
                }
                break;
                case WrappedMessage::WrappedMessageType::SESSION_MSG:
                {
                    // TODO:
                    //mServerPtr->on_
                    mServerPtr->on_msg(msg.mSessionMsg->first,msg.mSessionMsg->second);
                }
            }
        }
    }
}
