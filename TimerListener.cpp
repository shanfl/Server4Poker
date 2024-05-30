#include "TimerListener.hpp"
#include "ServerBase.h"
namespace Base {
    TimerAlloc::TimerAlloc(ServerBase*serverbase):mServerPtr(serverbase)
    {
    }

    TimerAlloc::~TimerAlloc()
    {
        this->mServerPtr->log(LogLevel::info, __FUNCTION__);
        for(auto&it:mTimers){
            it.second->stop();
        }
    }

    void TimerAlloc::init(ServerBase*serverbase)
    {
        if(this->mServerPtr == nullptr)
            this->mServerPtr = serverbase;

        mAsync.init(this->server_ptr());
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
        ITimerListenerWPtr wptr= item.wptr;
        mTimeHandle->on<uvw::timer_event>([this,baseServer,wptr,_id,_delay,_interval](auto&,auto&){
            baseServer->__on_timer(wptr,_id,_interval);
        });
    }
}  // namespace Base



