#pragma once
#include "Msg.def.h"
#include "TimerListener.hpp"

namespace Base {
    class WrappedMessageBuilder
    {
    public:
        WrappedMessageBuilder&set(std::weak_ptr<TimerAlloc> ta){
            timercaller = ta;
            return *this;
        }

        WrappedMessageBuilder&set(Message&msg){
            mMsg = msg;
            return *this;
        }

    public:
        Message mMsg;
        std::weak_ptr<TimerAlloc> timercaller;
    };

} // namespace Base
