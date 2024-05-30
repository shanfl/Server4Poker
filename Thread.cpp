#include "ServerBase.h"
#include "Thread.hpp"
namespace Base {
	Thread::Thread(ServerBase* baseserver, int idx) : mServerPtr(baseserver), mIndex(idx)
	{
		mRun = true;
		mThd = std::thread(Thread::on_work, this);
	}

    Thread::~Thread(){
        stop();
        if(mThd.joinable())
            mThd.join();
    }

	void Thread::push(WrappedMessage& msg)
    {
        if(!mRun) return;
        mMsgPool.push(msg);
	}

	std::vector<WrappedMessage> Thread::get(int maxnum)
    {
        if(!mRun) return {};
        return mMsgPool.get(maxnum);
	}

	bool Thread::get(WrappedMessage& msg)
	{
		std::vector<WrappedMessage> v = get(1);
		if (v.size() == 0) return false;
		msg = v[0];
		return true;
	}

	void Thread::on_work(Thread* ptr)
	{
        ptr->mWorkThreadId = std::this_thread::get_id();
		ptr->msg_loop();
	}

    void Thread::stop()
    {
        mRun = false;
    }

	void Thread::msg_loop() {
		while (mRun) {
			WrappedMessage msg;
			bool b = get(msg);
			if (!b)
			{
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				continue;
			}

			switch (msg.mType) {
			case WrappedMessage::WrappedMessageType::TIMER_TICK:
            {
                ITimerListenerWPtr ptr = msg.mTimerTick->first;
                auto sptr = ptr.lock();
                if(sptr)
                {
                    sptr->__on_timer(msg.mTimerTick->second.id, msg.mTimerTick->second.interval,this->mIndex);
                }
			}
			break;
			case WrappedMessage::WrappedMessageType::SESSION_MSG:
			{
				std::get<2>(*msg.mSessionMsg)(std::get<0>(*msg.mSessionMsg), std::get<1>(*msg.mSessionMsg));
			}
			break;

			case WrappedMessage::WrappedMessageType::NATS_MSG:
			{
				this->mServerPtr->on_nats_pub(msg.mNatsMsg->first,
					msg.mNatsMsg->second.sub,
					msg.mNatsMsg->second.id,
					msg.mNatsMsg->second.msg,
					msg.mNatsMsg->second.reply_to);
			}
            break;
            case WrappedMessage::WrappedMessageType::NATS_REQUESTPLY:
                msg.mNatsRequestReplyMsg->second.cb(msg.mNatsRequestReplyMsg->first,msg.mNatsRequestReplyMsg->second.msg,msg.mNatsRequestReplyMsg->second.error);
                break;
			default:
				break;
			}

            std::this_thread::sleep_for(std::chrono::milliseconds(300));
		}
	}
}
