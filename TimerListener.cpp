#include "TimerListener.hpp"
#include "ServerBase.h"
namespace Base {
    TimerAlloc::TimerAlloc(ServerBase*serverbase):mServerPtr(serverbase)
    {
    }

    TimerAlloc::~TimerAlloc()
    {
        this->mServerPtr->log(LogLevel::info, __FUNCTION__);
        if(this != mServerPtr)
            mServerPtr->rem_timer_alloc(this);

        for(auto&it:mTimers){
            it.second->stop();// = nullptr;
        }
    }

    void TimerAlloc::init(ServerBase*serverbase)
    {
        if(this->mServerPtr == nullptr)
            this->mServerPtr = serverbase;

        mAsync.init(this->server_ptr());
        mServerPtr->add_timer_alloc(this);
        mAsync.set_do_fn([this](){
            std::lock_guard<std::mutex> lk(mMutexTimeOps);
            for(auto&it:mTimeOps){
                if(it.op == TimeOpe::add){
                    mTimers[it.id] = std::make_shared<UvwTimerLisenter>(this,it);
                    mTimers[it.id]->start();
                }else if(it.op == TimeOpe::del){
                    if(mTimers.find(it.id) != mTimers.end()){
                        mTimers[it.id]->stop();
                        mTimers.erase(it.id);
                    }
                }
            }
            mTimeOps.clear();
        });
    }

    void TimerAlloc::__timer_tick(int id,int delay,int interval)
    {
        int index = thd_idx_timer();
        if(this == mServerPtr || index < 0 || mServerPtr->mThreads.size() == 0){
            this->on_timer_tick(id,delay,interval);     // libuv main-loop thread
        }else
        {
            //构建protobuf timermsg；
            //mServerPtr->dispatch_work();
            Message msg;
            WrappedMessage w_msg;
            w_msg.set(this,id,delay,interval);
            //
            mServerPtr->dispatch_th_work(index,w_msg);
        }
    }

    //-----------------------------------------------------------------------------
    // UvwTimerLisenter
    UvwTimerLisenter::UvwTimerLisenter(TimerAlloc*ta,TimerAlloc::TimeItem item)
    {
        mTimerAlloc = ta;
        mTimeItem = item;
        mTimeHandle = ta->server_ptr()->loop()->resource<uvw::timer_handle>();
        ServerBase* baseServer = ta->server_ptr();
        int _id = item.id;
        int _delay = item.delay;
        int _interval = item.interval;
        mTimeHandle->on<uvw::timer_event>([this,baseServer,_id,_delay,_interval](auto&,auto&){
            if(mTimerAlloc) //TODO: not thread safe
                mTimerAlloc->__timer_tick(_id,_delay,_interval);
        });
    }
}  // namespace Base



