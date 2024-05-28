#pragma once
#include "Msg.def.h"
#include "TimerListener.hpp"
#include "Session/Session.hpp"
#include "nats_client/natsclient.hpp"

namespace uvw {
	class Session;
}

namespace Base {
	using SessionPtr = std::shared_ptr<uvw::Session>;
	using NatsClinetPtr = std::shared_ptr<uvw::nats_client>;

	using SESSION_FN = std::function<void(SessionPtr ptr, Message& msg)>;
	using NATS_FN = std::function<void(NatsClinetPtr ptr, Message& msg)>;

	class WrappedMessage
	{
		friend class Thread;
		friend class ServerBase;
	public:
		enum class WrappedMessageType
		{
			NONE,
			TIMER_TICK,
			SESSION_MSG,
			NATS_MSG,
		};

		struct NatsMsg
		{
			std::string sub;
			std::string reply_to;
			int32_t id;
			std::shared_ptr<ProtoMsg> msg;
		};

		using TimerTickPair = std::pair<std::weak_ptr<TimerAlloc>, TimerAlloc::TimeItem>;
		using SessionMsgPair = std::tuple< std::shared_ptr<uvw::Session>, Message, SESSION_FN>;
		using NatsMsgPair = std::pair<std::shared_ptr<uvw::nats_client>, NatsMsg>;

	public:
		WrappedMessage& set(std::weak_ptr<TimerAlloc> ta, int timerid, int delay, int repeat) {
			mTimerTick = std::make_shared<TimerTickPair>(std::make_pair(ta, TimerAlloc::TimeItem(timerid, delay, repeat)));
			mType = WrappedMessageType::TIMER_TICK;
			return *this;
		}

		WrappedMessage& set(std::shared_ptr<uvw::Session> session, Message& msg, SESSION_FN fn) {
			mSessionMsg = std::make_shared<SessionMsgPair>(std::make_tuple(session, msg, fn));
			mType = WrappedMessageType::SESSION_MSG;
			return *this;
		}

		WrappedMessage& set(std::shared_ptr<uvw::nats_client> client, std::string sub, std::string replyto, int32_t msgid, std::shared_ptr<ProtoMsg>msg) {
			mNatsMsg = std::make_shared<NatsMsgPair>(std::make_pair(client, NatsMsg{ sub,replyto,msgid,msg }));
			mType = WrappedMessageType::NATS_MSG;
			return *this;
		}
	private:
		std::shared_ptr<TimerTickPair>      mTimerTick;
		std::shared_ptr<SessionMsgPair>     mSessionMsg;
		std::shared_ptr<NatsMsgPair>        mNatsMsg;
		WrappedMessageType mType;
	};

} // namespace Base
