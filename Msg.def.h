#pragma once
#include <inttypes.h>
#include <string>
#include <memory>
//#include <google/protobuf/message_lite.h>
enum CompressMethod
{
	CM_NONECM = 0,
	CM_ZIP,
};

namespace google {
	namespace protobuf {
		class MessageLite;
	}
}

using ProtoMsg = google::protobuf::MessageLite;

namespace Base {

	static const std::string header_flags = "%$%^@aa@";

#pragma pack(1)
	struct MsgRawHeader
	{
		char flags[8] = { '%','$','%','^','@','a','a','@' };
		int8_t cm = 0;
		uint32_t msg_id = 0;
		uint32_t msg_len = 0;
		uint32_t msg_unpack_len = 0;
		uint16_t cookie_len = 0;
	};
#pragma pack()

	constexpr static int HEADER_LEN = sizeof(MsgRawHeader);

	struct MsgHeader :public MsgRawHeader
	{
		std::string cookie;
	};

	struct WsMsgHeader
	{
		int32_t id;
		int32_t zipped;
		std::string cookie;
	};

	class Message
	{

	public:

		static std::string z_compress(std::string& str, bool& err);
		static std::string z_uncompress(std::string& str, size_t uncompress_len, bool& err);

		static std::string fast_split(std::string& data, bool& err);


		static bool Decode(std::string& data, MsgHeader& hdr, std::string& body);

		static Message Decode(std::shared_ptr<ProtoMsg> ptr, std::string msgwith_hdeader, bool& err);

		static std::string Encode(uint32_t msg_id, std::string str, std::string cookie = "");

		static bool DecodeWS(std::string& data, WsMsgHeader& hdr, std::string& body);


		bool parser(std::string& data);
		//std::dynamic_pointer_cast
		template<typename T>
		std::shared_ptr<T> GetProtoMsg()
		{
			return std::dynamic_pointer_cast<T>(proto_msg);
		}

		Message& SetProtoPtr(std::shared_ptr<ProtoMsg> ptr);

		uint32_t MsgId();
		Message& SetMsgId(uint32_t id);
		Message& SetNatsSubject(std::string& sub);
		Message& SetNatsReplyto(std::string& replyto);
		std::string Subject_Nats();
		std::string Replyto_Nats();
	protected:
		std::shared_ptr<ProtoMsg> proto_msg;
	public:
		MsgHeader mHeader;
		std::string mCookie;
	private:
		std::string mNatsSubject;
		std::string mNatsReplyto;

	public:
		WsMsgHeader mWsHeader;
	};
} // namespace Base
