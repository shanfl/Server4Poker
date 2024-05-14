#include "TimerListener.hpp"
#include "ServerBase.h"
namespace Base {
    TimerAlloc::TimerAlloc(ServerBase*serverbase):mServerPtr(serverbase),mAsync(serverbase)
    {
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
        if(index < 0){
            this->on_timer_tick(id,delay,interval);     // libuv main-loop thread
        }else
        {
            //构建protobuf timermsg；
            //mServerPtr->dispatch_work();
        }
    }

    //-----------------------------------------------------------------------------
    // UvwTimerLisenter
    UvwTimerLisenter::UvwTimerLisenter(TimerAlloc*ta,TimerAlloc::TimeItem item)
    {
        mTimeItem = item;
        mTimeHandle = ta->server_ptr()->loop()->resource<uvw::timer_handle>();

        int _id = item.id;
        int _delay = item.delay;
        int _interval = item.interval;
        mTimeHandle->on<uvw::timer_event>([this,_id,_delay,_interval](auto&,auto&){
            mTimerAlloc->__timer_tick(_id,_delay,_interval);
        });
    }
}  // namespace Base



