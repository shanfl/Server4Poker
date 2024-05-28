#include "ServerBase.h"
#include "Thread.hpp"
namespace Base {
	Thread::Thread(ServerBase* baseserver, int idx) : mServerPtr(baseserver), mIndex(idx)
	{
		mRun = true;
		mThd = std::thread(Thread::on_work, this);
	}

	void Thread::push(WrappedMessage& msg)
	{
		mMsgPool.push(msg);
	}

	std::vector<WrappedMessage> Thread::get(int maxnum)
	{
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
		ptr->msg_loop();
	}

	void Thread::msg_loop() {
		while (mRun) {
			WrappedMessage msg;
			bool b = get(msg);
			if (!b)
			{
				std::this_thread::sleep_for(std::chrono::microseconds(10));
				continue;
			}

			switch (msg.mType) {
			case WrappedMessage::WrappedMessageType::TIMER_TICK:
			{
				std::shared_ptr<TimerAlloc> ptr = msg.mTimerTick->first.lock();
				if (ptr)
					ptr->on_timer_tick(msg.mTimerTick->second.id, msg.mTimerTick->second.delay, msg.mTimerTick->second.interval);
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
			default:
				break;

			}
		}
	}
}
