#pragma once
#include "uvw.hpp"
#include <unordered_map>
#include "AsyncUvw.hpp"
#include <mutex>
namespace Base {
    class ITimerListener
    {
    public:
        virtual int delay() = 0;
        virtual int interval() = 0;
        virtual int timer_id() = 0;
        virtual int start() = 0;
        virtual void stop() = 0;
    };

    class ServerBase;
    // TODO: std::enable_shared_from_this<TimerAlloc> is wrong
    class TimerAlloc
    {
    public:
        enum TimeOpe
        {
            none,
            add,
            del,
        };

        struct TimeItem
        {
            TimeItem(){}
            TimeItem(int _id,int _delay,int _interval):id(_id),delay(_delay),interval(_interval){}
            TimeItem(int _id): id(_id){
                delay = 0;
                interval = 0;
            }

            int id = -1;
            int delay = 0;
            int interval = 0;
        };

        struct TimeOperation:public TimeItem
        {
            TimeOperation(){}
            TimeOperation(int id,int delay,int interval):TimeItem(id,delay,interval),op(TimeOpe::add){}
            TimeOperation(TimeOpe _op,int _id):TimeItem(_id),op(_op){}

            TimeOpe op;
        };

    public:
        TimerAlloc(){}
        TimerAlloc(ServerBase*serverbase);
        ~TimerAlloc();

        void init(ServerBase*serverbase);

        int add_timer(int id,int delay,int interval)
        {
            std::lock_guard<std::mutex> lk(mMutexTimeOps);
            mTimeOps.push_back(TimeOperation{id,delay,interval});
            mAsync.do_sync();
            return id;
        }

        bool rem_timer(int id){
            std::lock_guard<std::mutex> lk(mMutexTimeOps);
            mTimeOps.push_back(TimeOperation{TimeOpe::del,id});
            mAsync.do_sync();
            return true;
        }

        virtual void __timer_tick(int id,int delay,int interval);

        virtual void on_timer_tick(int id,int delay,int interval) = 0;

        virtual int  thd_idx_timer() = 0;

        ServerBase* server_ptr() {return mServerPtr;}
    protected:
        std::unordered_map<int,std::shared_ptr<ITimerListener>> mTimers;
        std::mutex mMutexTimers;

        std::vector<TimeOperation> mTimeOps;
        std::mutex mMutexTimeOps;

        AsyncUvw mAsync;

        ServerBase* mServerPtr = nullptr;
    };

    class UvwTimerLisenter:public ITimerListener
    {
    public:
        UvwTimerLisenter(TimerAlloc*ta,TimerAlloc::TimeItem item);

        TimerAlloc::TimeItem mTimeItem;
        std::shared_ptr<uvw::timer_handle> mTimeHandle;
        TimerAlloc* mTimerAlloc = nullptr;
        virtual int start(){    mTimeHandle->start(uvw::timer_handle::time{delay()},uvw::timer_handle::time{interval()}); return mTimeItem.id;}
        virtual int delay(){return mTimeItem.delay;}
        virtual int interval(){return mTimeItem.interval;}
        virtual int timer_id() {return mTimeItem.id;}
        virtual void stop(){ mTimeHandle->stop(); mTimeHandle->reset(); mTimerAlloc = nullptr;}
    };
}

