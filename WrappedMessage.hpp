#pragma once
#include "Msg.def.h"
#include "TimerListener.hpp"
#include "Session/Session.hpp"

namespace uvw {
    class Session;
}

namespace Base {
    class WrappedMessage
    {
        friend class Thread;
    public:
        enum class WrappedMessageType
        {
            NONE,
            TIMER_TICK,
            SESSION_MSG,
        };

        using TimerTickPair = std::pair<std::weak_ptr<TimerAlloc>,TimerAlloc::TimeItem>;
        using SessionMsgPair = std::pair< std::shared_ptr<uvw::Session>,Message> ;
    public:
        WrappedMessage&set(std::weak_ptr<TimerAlloc> ta,int timerid,int delay,int repeat){
            mTimerTick = std::make_shared<TimerTickPair>(std::make_pair(ta,TimerAlloc::TimeItem(timerid,delay,repeat)));
            mType = WrappedMessageType::TIMER_TICK;
            return *this;
        }

        WrappedMessage&set(std::shared_ptr<uvw::Session> session,Message &msg){
            mSessionMsg = std::make_shared<SessionMsgPair>(std::make_pair(session,msg));
            mType = WrappedMessageType::SESSION_MSG;
            return *this;
        }
    private:
        std::shared_ptr<TimerTickPair>      mTimerTick;
        std::shared_ptr<SessionMsgPair>     mSessionMsg;
        WrappedMessageType mType;
    };

} // namespace Base
