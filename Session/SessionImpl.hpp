#ifndef SESSIONIMPL_HPP
#define SESSIONIMPL_HPP
#include "uvw.hpp"
#include <map>
#include <string>
#include <string.h>
#include "SessionDef.h"
#include "url.hpp"
#include "IdMaker.h"

class Session;
namespace uvw {
	enum class HaproxyState
	{
		WAIT_MORE,
		YES,
		NO,
	};

	enum class WebsocketState
	{
		WAIT_MORE,
		YES,
		HANDSHAKE_DONE,
		NO,
	};

	struct WsFrameHeaderLite
	{
		uint8_t fin;
		uint8_t rsv1;
		uint8_t rsv2;
		uint8_t rsv3;
		uint8_t opcode;
		uint8_t mask;
		uint8_t PayloadLen;
	};

	struct WsFrame
	{
		WsFrameHeaderLite header;
		int64_t  datalen;
		uint32_t  masking_key = 0;
		std::string content;

		int opcode() {
			return header.opcode;
		}

		bool IsFinal() {
			return header.fin == 1;
		}

		static inline void xor_buffer(char* src, size_t len, uint32_t key) {
			for (size_t i = 0; i < len; i++) {
				src[i] ^= key >> i % 4 * 8 & 255;
			}
		}

		static std::string xor_buffer(std::string str, uint32_t key) {

			for (size_t i = 0; i < str.length(); i++) {
				str[i] ^= key >> i % 4 * 8 & 255;
			}
			return str;
		}

		bool Parser(std::string& msgbuf, size_t& offset)
		{
			size_t bufsize = msgbuf.size();
			int off_data = 0;
			if (bufsize < 4) return false;
			char a = msgbuf.c_str()[0];
			char b = msgbuf.c_str()[1];

			header.fin = (a & FIN) >> 7;
			header.rsv1 = (a & RSV1) >> 6;
			header.rsv2 = (a & RSV2) >> 5;
			header.rsv3 = (a & RSV3) >> 4;
			header.opcode = (a & OPCODE) & 0x0F;
			header.mask = (b & MASK) >> 7;
			header.PayloadLen = (b & PAYLOADLEN) & 0x7F;
			off_data += 2;

			if (header.PayloadLen == 126) {
				if (bufsize < (off_data + 2)) return false;
				char byte2[2];
				byte2[0] = msgbuf.c_str()[off_data];
				byte2[1] = msgbuf.c_str()[off_data + 1];

				datalen = (byte2[0] & 0xff) << 8;
				datalen |= (byte2[1] & 0xff);
				off_data += 2;
			}
			else if (header.PayloadLen == 127) {
				if (bufsize < (off_data + 8)) return false;
				datalen = 0;
				datalen |= (msgbuf.c_str()[off_data] & 0xFF) << 56;
				datalen |= (msgbuf.c_str()[off_data + 1] & 0xFF) << 48;
				datalen |= (msgbuf.c_str()[off_data + 2] & 0xFF) << 40;
				datalen |= (msgbuf.c_str()[off_data + 3] & 0xFF) << 32;
				datalen |= (msgbuf.c_str()[off_data + 4] & 0xFF) << 24;
				datalen |= (msgbuf.c_str()[off_data + 5] & 0xFF) << 16;
				datalen |= (msgbuf.c_str()[off_data + 6] & 0xFF) << 8;
				datalen |= (msgbuf.c_str()[off_data + 7] & 0xFF);

				off_data += 8;
			}
			else {
				datalen = header.PayloadLen;
			}

			if (header.mask) { // masking-key
				if (bufsize < (off_data + 4))return false;
				memcpy(&masking_key, msgbuf.c_str() + off_data, 4);
				off_data += 4;
			}

			{
				if ((bufsize - off_data) < datalen)
					return false;

				content = std::string((char*)(msgbuf.c_str() + off_data), datalen);
				if (header.mask)
					content = xor_buffer(content, masking_key);
				off_data += datalen;
				offset = off_data;
				return true;
			}
		}
	};

	class WsProtoII
	{
	public:

		std::vector<WsMsg> get()
		{
			std::vector<WsMsg> msgs;
			msgs = msgvec;
			msgvec.clear();
			return msgs;
		}
		//    void append(std::string str) {
		//        //msgbuf.Append((const uint8_t*)str.c_str(), str.length());
		//        msgbuf += str;
		//    }

		void setBuffPtr(std::string* ptr) {
			msgbuf = ptr;
		}

		void pareser() {

			size_t offset = 0;

			WsFrame frame;
			bool suc = frame.Parser(*msgbuf, offset);
			if (suc) {
				if (frame.IsFinal()) {
					WsMsg ws{ (SocketOpcode)frame.opcode(),frame.content };
					msgvec.push_back(ws);
					//frames.push_back(frame);
					//msgbuf.Shift(offset);
					*msgbuf = msgbuf->substr(offset);
				}
				else {
					unfinished.data += frame.content;
					unfinished.opcode = (SocketOpcode)frame.opcode();
				}
			}
		}

		WsMsg unfinished;
		std::vector<WsMsg> msgvec;
		std::string* msgbuf = nullptr;
	};


	class SessionImpl
	{
		typedef std::map<std::string, std::string> WebSocketHeaders;
		friend class Session;
	public:
		SessionImpl(Session* session, std::shared_ptr<uvw::loop> loop);
		SessionImpl(Session* session, std::shared_ptr<uvw::loop> loop, std::shared_ptr<uvw::tcp_handle>& tcphandle);

        ~SessionImpl();

        void id();

		void read();
		void send(std::string data);
		void ws_send(const char* buf, size_t length, SocketOpcode op);
		void raw_send(const char* buf, size_t length);
		//void send();
		void close();
		void connect(std::string host);
	protected:
        void set_ws_serectkey(std::string serect_key);
        void set_session_state(SessionState sstate);
		void init_state();
		void init_tcp();
		bool is_client_side();
		bool is_websocket();
		void on_tcp_connected(SideClient side, std::shared_ptr<uvw::tcp_handle> hdl = nullptr);
		void on_data_local(std::string data);
		void on_data_remote(std::string data);

		void send_http_request(const WebSocketHeaders& custom_headers);

        void set_tcpmsg_spliter(std::function<std::string(std::string& data,bool &err)> f);

        void handle_tcpdata();
	private:
		Session* mSessionPtr = nullptr;

        SessionState mSessionState;
        std::chrono::system_clock::time_point mSStateStarttime;  // session-state start time

        HaproxyState mHaproxyState = HaproxyState::WAIT_MORE;
		WebsocketState mWebsocketState = WebsocketState::WAIT_MORE;
		bool mHandShakeDone = false;
		std::shared_ptr<uvw::loop> mLoop;
		std::shared_ptr<uvw::tcp_handle> mTcpHandler;
		//std::string mData;
		SideClient mSideClient;
		std::string mData;
		WsProtoII mWsDataParser;

        //Mask, RFC 6455 Section 10.3
        int mMaskingKey = 0;
		bool mIsWebsocket = false;
        std::string mSecretKey = "dGhlIHNhbXBsZSBub25jZQ==";
		Url mUri;

        std::function<std::string(std::string& data,bool &err)> mTcpDataUnpack;

        int64_t mId = 0;
	};

}  // namespace


#endif // SESSIONIMPL_HPP
