#pragma once
#include <thread>
#include <vector>
#include "MessagePool.h"
#include "Msg.def.h"
#include "WrappedMessage.hpp"
#include <mutex>
#include <thread>
namespace Base
{
	class ServerBase;

	using MsgPool = MessagePool<WrappedMessage>;

	class Thread
	{
	public:
		Thread(ServerBase* baseserver, int index);
		~Thread();

		void push(WrappedMessage& msg);

		void stop();

		std::vector<WrappedMessage> get(int maxnum);

		bool get(WrappedMessage& msg);

		std::thread::id get_thd_id() { return mWorkThreadId; }

		int get_index() { return mIndex; }

		static void on_work(Thread* ptr);

		void msg_loop();
	private:
		ServerBase* mServerPtr = nullptr;
		int mIndex;
		std::thread mThd;

		MessagePool<WrappedMessage> mMsgPool;
		bool mRun = false;
		std::thread::id mWorkThreadId;// { 0 };
	};
}   // namespace Base
