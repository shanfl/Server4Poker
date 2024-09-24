#include "Session.hpp"
#include "SessionImpl.hpp"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <string.h>
#include <cstring>
#include "endian.h"

static IdMaker idgen(1,1);

namespace uvw {

	class WebsocketHelper {
	public:

		static void write_uint8(char* dest, size_t dest_len, uint8_t v, size_t& off) {
			dest[off] = v;
			off += 1;
		}

		static uint32_t read_uint32(const char* dest, size_t dest_len, size_t& off) {
			uint32_t v;
			memcpy(&v, dest + off, 4);
			off += 4;
			return v;
		}

		static inline void xor_buffer(char* src, size_t len, uint32_t key) {
			for (size_t i = 0; i < len; i++) {
				src[i] ^= key >> i % 4 * 8 & 255;
			}
		}

		static size_t WebSocketCreateFrameHeader(char* dest, size_t dest_len, SocketOpcode opcode, size_t payload_length, char* mask)
		{
			size_t off = 0;
			write_uint8(dest, dest_len, 0x80 | opcode, off);

			if (payload_length < 126) {
				dest[off++] = (*mask == 0) ? (payload_length & 0x7f) : (payload_length | 0x80);
			}
			else if (payload_length < 65536) {
				dest[off++] = (*mask == 0) ? 126 : 126 | 0x80;
				dest[off++] = (payload_length >> 8) & 0xff;
				dest[off++] = (payload_length) & 0xff;
			}
			else {
				dest[off++] = (*mask == 0) ? 127 : 127 | 0x80;
				dest[off++] = (payload_length >> 56) & 0xff;
				dest[off++] = (payload_length >> 48) & 0xff;
				dest[off++] = (payload_length >> 40) & 0xff;
				dest[off++] = (payload_length >> 32) & 0xff;
				dest[off++] = (payload_length >> 24) & 0xff;
				dest[off++] = (payload_length >> 16) & 0xff;
				dest[off++] = (payload_length >> 8) & 0xff;
				dest[off++] = (payload_length) & 0xff;
			}

			if (*mask) {
				memcpy(dest + off, mask, 4);
				off += 4;
			}

			return off;
		}

		static std::string trim(std::string str)
		{
			//printf("TRIM\n");
			char* whitespace = " \t\r\n";
			std::string::size_type pos = str.find_last_not_of(whitespace);
			if (pos != std::string::npos) {
				str.erase(pos + 1);
				pos = str.find_first_not_of(whitespace);
				if (pos != std::string::npos) str.erase(0, pos);
			}
			else {
				return std::string();
			}
			return str;
		}

		static std::vector<std::string> string_split(const std::string& str, std::string delim) {
			std::size_t previous = 0;
			std::size_t current = str.find_first_of(delim);
			std::vector<std::string> elems;
			while (current != std::string::npos) {
				if (current > previous) {
					elems.push_back(str.substr(previous, current - previous));
				}
				previous = current + 1;
				current = str.find_first_of(delim, previous);
			}
			if (previous != str.size()) {
				elems.push_back(str.substr(previous));
			}
			return elems;
		}

		/* request
			GET /chat HTTP/1.1
			Host: server.example.com
			Upgrade: websocket
			Connection: Upgrade
			Sec-WebSocket-Key: dGhlIHNhbXBsZSBub25jZQ==
			Origin: http://example.com
			Sec-WebSocket-Protocol: chat, superchat
			Sec-WebSocket-Version: 13
		 */

		 /* response
			 HTTP/1.1 101 Switching Protocols
			 Upgrade: websocket
			 Connection: Upgrade
			 Sec-WebSocket-Accept: s3pPLMBiTxaQ9kYGzzhZRbK+xOo=
			 Sec-WebSocket-Protocol: chat
			 Sec-WebSocket-Version: 13
		  */
		static WebsocketState handshake_request(std::string& data, std::map<std::string, std::string>& resmap)
		{
			if (data.length() <= 8) return WebsocketState::WAIT_MORE;
			std::string first3(data.c_str(), 3);

			//std::transform(first3.begin(),first3.end(),first3.begin(),std::toupper);
			if (first3 != "GET" && first3 != "get") {
				return WebsocketState::NO;
			}

			size_t pos = data.find("\r\n\r\n");
			if (pos == std::string::npos) {
				return WebsocketState::WAIT_MORE;
			}
			else {
				std::string rdata = data.substr(0, pos - 4);
				data = data.substr(pos + 4);

				std::vector<std::string> strlist = string_split(rdata, "\r\n");
				for (auto& it : strlist) {
					size_t pos = it.find_first_of(":");
					if (pos == std::string::npos) continue;
					std::string k = it.substr(0, pos);
					std::string v = it.substr(pos + 1);
					resmap[trim(k)] = trim(v);
				}
			}
			return WebsocketState::YES;
		}

		static WebsocketState handshake_response(std::string& data, std::map<std::string, std::string>& resmap)
		{
			if (data.length() <= 8) return WebsocketState::WAIT_MORE;
			std::string first3(data.c_str(), 5);

			//std::transform(first3.begin(),first3.end(),first3.begin(),std::toupper);
			if (first3 != "HTTP/") {
				return WebsocketState::NO;
			}

			size_t pos = data.find("\r\n\r\n");
			if (pos == std::string::npos) {
				return WebsocketState::WAIT_MORE;
			}
			else {
				std::string rdata = data.substr(0, pos - 4);
				data = data.substr(pos);

				std::vector<std::string> strlist = string_split(rdata, "\r\n");
				for (auto& it : strlist) {
					size_t pos = it.find_first_of(":");
					if (pos == std::string::npos) continue;
					std::string k = it.substr(0, pos);
					std::string v = it.substr(pos + 1);
					resmap[trim(k)] = trim(v);
				}
			}
			return WebsocketState::YES;
		}

		static std::string answer_handshake(std::string key, std::string protocol)
		{
			unsigned char digest[20]; // 160 bit sha1 digest

			std::string answer;
			answer += "HTTP/1.1 101 Switching Protocols\r\n";
			answer += "Upgrade: WebSocket\r\n";
			answer += "Connection: Upgrade\r\n";
			if (key.length() > 0) {
				std::string accept_key;
				char wskey[128] = { 0 };
				accept_key += key;
				accept_key += "258EAFA5-E914-47DA-95CA-C5AB0DC85B11"; //RFC6544_MAGIC_KEY
				int len = accept_key.length();
				memcpy(wskey, accept_key.c_str(), accept_key.length());

				//printf("INTERMEDIATE_KEY:(%s)\n", accept_key.data());
				char accept_str[32];
				accept_str[sha1base64((uint8_t*)wskey, 24 + 36, accept_str)] = 0;
				answer += "Sec-WebSocket-Accept: " + (std::string(accept_str)) + "\r\n";
			}
			if (protocol.length() > 0) {
				answer += "Sec-WebSocket-Protocol: " + (protocol)+"\r\n";
			}
			answer += "\r\n";
			return answer;
		}

		static uint32_t rol(uint32_t value, uint32_t bits) { return (value << bits) | (value >> (32 - bits)); }

		static uint32_t sha1base64(uint8_t* in, uint64_t in_len, char* out) {
			uint32_t h0[5] = { 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0 };
			uint64_t total_len = in_len;
			in[total_len++] = 0x80;
			int padding_size = (64 - (total_len + 8) % 64) % 64;
			while (padding_size--) in[total_len++] = 0;
			for (uint64_t i = 0; i < total_len; i += 4) {
				uint32_t& w = *(uint32_t*)(in + i);
				w = be32toh(w);
			}
			*(uint32_t*)(in + total_len) = (uint32_t)(in_len >> 29);
			*(uint32_t*)(in + total_len + 4) = (uint32_t)(in_len << 3);
			for (uint8_t* in_end = in + total_len + 8; in < in_end; in += 64) {
				uint32_t* w = (uint32_t*)in;
				uint32_t h[5];
				memcpy(h, h0, sizeof(h));
				for (uint32_t i = 0, j = 0; i < 80; i++, j += 4) {
					uint32_t& a = h[j % 5], & b = h[(j + 1) % 5], & c = h[(j + 2) % 5], & d = h[(j + 3) % 5], & e = h[(j + 4) % 5];
					if (i >= 16) w[i & 15] = rol(w[(i + 13) & 15] ^ w[(i + 8) & 15] ^ w[(i + 2) & 15] ^ w[i & 15], 1);
					if (i < 40) {
						if (i < 20)
							e += ((b & (c ^ d)) ^ d) + 0x5A827999;
						else
							e += (b ^ c ^ d) + 0x6ED9EBA1;
					}
					else {
						if (i < 60)
							e += (((b | c) & d) | (b & c)) + 0x8F1BBCDC;
						else
							e += (b ^ c ^ d) + 0xCA62C1D6;
					}
					e += w[i & 15] + rol(a, 5);
					b = rol(b, 30);
				}
				for (int i = 0; i < 5; i++) h0[i] += h[i];
			}
			const char* base64tb = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
			uint32_t triples[7] = { h0[0] >> 8,
								   (h0[0] << 16) | (h0[1] >> 16),
								   (h0[1] << 8) | (h0[2] >> 24),
								   h0[2],
								   h0[3] >> 8,
								   (h0[3] << 16) | (h0[4] >> 16),
								   h0[4] << 8 };
			for (uint32_t i = 0; i < 7; i++) {
				out[i * 4] = base64tb[(triples[i] >> 18) & 63];
				out[i * 4 + 1] = base64tb[(triples[i] >> 12) & 63];
				out[i * 4 + 2] = base64tb[(triples[i] >> 6) & 63];
				out[i * 4 + 3] = base64tb[triples[i] & 63];
			}
			out[27] = '=';
			return 28;
		}
	};


    //-----------------------------------------------------
	SessionImpl::SessionImpl(Session* session, std::shared_ptr<uvw::loop> loop)
	{
		mSessionPtr = session;
		mLoop = loop;

        mId = idgen.nextId();
	}

	SessionImpl::SessionImpl(Session* session, std::shared_ptr<uvw::loop> loop, std::shared_ptr<uvw::tcp_handle>& tcphandle)
	{
		mSessionPtr = session;
		mLoop = loop;
		mTcpHandler = tcphandle;

        mId = idgen.nextId();
	}

	SessionImpl::~SessionImpl()
	{
		std::clog << __FUNCTION__ << std::endl;
	}

    int64_t SessionImpl::id()
    {
        return mId;
    }

	void SessionImpl::connect(std::string host)
	{
		mUri = Url(host);
		mIsWebsocket = false;
		if (mUri.scheme() == "ws") {
			mIsWebsocket = true;
		}

		if (mTcpHandler) {
			mTcpHandler->reset();
			mTcpHandler->close();
			mData = "";
		}

		mTcpHandler = mLoop->resource<uvw::tcp_handle>();

		init_tcp();

        int ret = this->mTcpHandler->connect(mUri.host(), stoi(mUri.port()));
        this->set_session_state(SessionState::CONNECTING);
	}

    void SessionImpl::set_ws_serectkey(std::string serect_key)
    {
        mSecretKey = serect_key;
    }

    void SessionImpl::set_session_state(SessionState sstate)
    {
        mSessionState = sstate;
        mSStateStarttime = std::chrono::system_clock::now();
    }

	void SessionImpl::init_state()
	{
		mHaproxyState = HaproxyState::WAIT_MORE;
		mWebsocketState = WebsocketState::WAIT_MORE;
	}

	void SessionImpl::read() {
        if (mTcpHandler)
            mTcpHandler->read();
    }

	void SessionImpl::raw_send(const char* buf, size_t length)
	{
		if (mTcpHandler)
			mTcpHandler->write((char*)buf, length);
	}

    void SessionImpl::close()
    {
        if(mSessionState >= CONNECTING && mSessionState <= CONNECTED){
        if(!mTcpHandler) {
            set_session_state(SessionState::CLOSED);
            return;
        }

        mTcpHandler->close();
        set_session_state(SessionState::CLOSING);
        }
    }

	bool SessionImpl::is_client_side() {
		return this->mSideClient == SideClient::LOCAL_CLIENT;
	}

	void SessionImpl::init_tcp()
	{
		this->mTcpHandler->on<uvw::close_event>([this](const uvw::close_event&, uvw::tcp_handle&)
			{
				std::clog << "close_event\n";
                set_session_state(SessionState::CLOSED);
                this->mTcpHandler->reset();
                this->mTcpHandler = nullptr;
			});

		this->mTcpHandler->on<uvw::end_event>([this](const uvw::end_event&, uvw::tcp_handle& client) {
			std::clog << "end_event\n";
			this->mTcpHandler->close();
			});

		this->mTcpHandler->on<uvw::data_event>([this](const uvw::data_event& dev, uvw::tcp_handle& client) {
			std::clog << "data_event\n";
			if (this->mTcpHandler) {
				if (this->is_client_side())
					this->on_data_local(std::string(dev.data.get(), dev.length));
				else
					this->on_data_remote(std::string(dev.data.get(), dev.length));
			}
			});

		this->mTcpHandler->on<uvw::connect_event>([this](uvw::connect_event& ev, uvw::tcp_handle& hdl) {
			std::clog << "connect_event\n";
			this->on_tcp_connected(SideClient::LOCAL_CLIENT);
			hdl.read();
			});

        this->mTcpHandler->on<uvw::error_event>([](const uvw::error_event&e, uvw::tcp_handle&) {
			/* handle errors */
            std::clog << "error_event: " << e.what() << std::endl;
			});
	}

	void SessionImpl::on_data_local(std::string data) {
		std::clog << __FUNCTION__ << std::endl;
		mData += data;
        if (is_websocket())
        {
			std::map<std::string, std::string> resmap;
			if (mWebsocketState == WebsocketState::WAIT_MORE) {
				std::clog << "data:" << data << std::endl;

				mWebsocketState = WebsocketHelper::handshake_response(mData, resmap);
				if (mWebsocketState == WebsocketState::WAIT_MORE)
				{
                    set_session_state(SessionState::PROXY_JUDGING);
                    return;
				}

				else if (mWebsocketState == WebsocketState::NO)
				{
					//  error
					std::clog << "error!" << std::endl;
					//TODO: close;                    
                    mSessionPtr->publish(on_error_event{"response not recv",-1});
                    close();
					return;
				}
				else if (mWebsocketState == WebsocketState::YES) {
					mWsDataParser.setBuffPtr(&mData);
                    set_session_state(SessionState::CONNECTED);
				}
			}

			if (mWebsocketState == WebsocketState::YES) {
				// 校验 response的Sec-WebSocket-Accept
				std::string appcet_string = resmap["Sec-WebSocket-Accept"];

                std::string accept_key = this->mSecretKey+ "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
                char wskey[128] = { 0 };
                memcpy(wskey, accept_key.c_str(), accept_key.length());
                char accept_str[32];
                accept_str[WebsocketHelper::sha1base64((uint8_t*)wskey, 24 + 36, accept_str)] = 0;
                std::string check_key = std::string(accept_str,accept_str+24);
                if(check_key != appcet_string){
                    this->mSessionPtr->publish(on_error_event{"Sec-WebSocket-Accept error",-1});
                    close();
                    return;
                }

                mWebsocketState = WebsocketState::HANDSHAKE_DONE;

				// on_open
				//on_open_event ev;
				mSessionPtr->publish(on_open_event{});
			}

			if (mWebsocketState == WebsocketState::HANDSHAKE_DONE) {
				mWsDataParser.pareser();
				std::vector<WsMsg> msgv = mWsDataParser.get();

                for(auto&it:msgv){
                    switch (it.opcode) {
                    case kTextFrame:
                    case kBinaryFrame:
                        mSessionPtr->publish(on_msg_event{it.opcode,it.data});
                        break;
                    case kClose:
                        mSessionPtr->publish(on_closewill_event{it.data});
                        break;
                    case kPing:
                        mSessionPtr->publish(on_ping_event{it.data});
                        break;
                    case kPong:
                        mSessionPtr->publish(on_pong_event{it.data});
                        break;
                    }
                }
			}
		}
		else {
			// TCP data
            handle_tcpdata();
		}
	}


	// handle client->server msg
	void SessionImpl::on_data_remote(std::string data) {
		mData += data;

		// haproxy


		// haproxy end


		// ws/tcp start
		std::map<std::string, std::string> reqmap;
		if (mWebsocketState == WebsocketState::WAIT_MORE) {
			std::clog << "data:\n" << data << std::endl;
			mWebsocketState = WebsocketHelper::handshake_request(mData, reqmap);
			if (mWebsocketState == WebsocketState::WAIT_MORE)
			{
				return;
			}
			else if (mWebsocketState == WebsocketState::NO)
			{
                mIsWebsocket = false;
			}
			else if (mWebsocketState == WebsocketState::YES) {
				mIsWebsocket = true;
				mWsDataParser.setBuffPtr(&mData);
			}
		}

		if (mWebsocketState == WebsocketState::NO) {
            handle_tcpdata();
            return;
		}

		if (mWebsocketState == WebsocketState::YES) {
			// 是 websocket
			std::string ans = WebsocketHelper::answer_handshake(reqmap["Sec-WebSocket-Key"], reqmap["Sec-WebSocket-Protocol"]);
			std::clog << "answer_handshake:\n" << ans << std::endl;
			raw_send(ans.c_str(), ans.length());
			mWebsocketState = WebsocketState::HANDSHAKE_DONE;
		}

		if (mWebsocketState == WebsocketState::HANDSHAKE_DONE) {
			mWsDataParser.pareser();
			std::vector<WsMsg> msgv = mWsDataParser.get();

            for(auto&it:msgv){
                switch (it.opcode) {
                case kTextFrame:
                case kBinaryFrame:
                    mSessionPtr->publish(on_msg_event{it.opcode,it.data});
                    break;
                case kClose:
                    mSessionPtr->publish(on_closewill_event{it.data});
                    break;
                case kPing:
                    mSessionPtr->publish(on_ping_event{it.data});
                    break;
                case kPong:
                    mSessionPtr->publish(on_pong_event{it.data});
                    break;
                default:
                    break;//?????
                }
            }
		}
		// ws/tcp end
	}

	void SessionImpl::on_tcp_connected(SideClient side, std::shared_ptr<uvw::tcp_handle> hdl) {
        std::clog << __FUNCTION__ << std::endl;
		mSideClient = side;
        set_session_state(SessionState::TCP_CONNECTED);
        if (side == SideClient::REMOTE_CLIENT) {
			mTcpHandler = hdl;
			init_tcp();
            //mTcpHandler->read();
            //set_session_state(SessionState::PROXY_JUDGING);  // 尚未实现
            set_session_state(SessionState::WS_JUDGING);  // 尚未实现
		}

        // 如果自己主动发起的connect，自己应该知道自己到底是tcp，还是websocket
        if (is_client_side())
        {
            if(is_websocket())
            {
                this->mMaskingKey = 1;
                mWebsocketState = WebsocketState::WAIT_MORE;
                // 发送upgrade
                WebSocketHeaders cwsh;
                this->send_http_request(cwsh);
                set_session_state(SessionState::WS_JUDGING);  // 客户端没有proxy的阶段
            }else{
                set_session_state(SessionState::CONNECTED);
            }
        }
	}

	void SessionImpl::send_http_request(const WebSocketHeaders& custom_headers)
	{
		std::clog << __FUNCTION__ << "\n";
		Url::Query query_params = mUri.query();
		std::string final_path = mUri.path();
		std::string host = mUri.host();
		if (query_params.size() > 0) {
			final_path += "?";
			for (int i = 0; i < query_params.size(); i++) {
				final_path += query_params[i].key();
				final_path += "=";
				final_path += query_params[i].val();
				if (query_params.size() - i > 1) {
					final_path += "&";
				}
			}
		}

		if (final_path.empty()) {
			final_path = "/";
		}

		std::string request =
			"GET " + final_path + " HTTP/1.1\r\n"
			"Host: " + host + "\r\n"
			"Connection: Upgrade\r\n"
			"Upgrade: websocket\r\n"
            "Sec-WebSocket-Key: "+ this->mSecretKey + "\r\n"
			"Sec-WebSocket-Version: 13\r\n";

		for (auto&& header : custom_headers) {
			request += header.first + ": " + header.second + "\r\n";
		}

		request += "\r\n";
		raw_send(request.data(), request.length());
        std::clog << "send:\n" << request.data() << std::endl;
	}

	void SessionImpl::send(std::string data)
	{
		if (is_websocket()) {
			ws_send(data.c_str(), data.length(), uvw::SocketOpcode::kTextFrame);
		}
		else {
			raw_send(data.c_str(), data.length());
		}
	}
	void SessionImpl::ws_send(const char* buf, size_t length, SocketOpcode op)
	{
		std::string frame(length + 14, 0);
		size_t header_length = WebsocketHelper::WebSocketCreateFrameHeader(frame.data(), frame.length(),
			op, length, (char*)&mMaskingKey);

		std::memcpy(frame.data() + header_length, buf, length);
		if (mMaskingKey) {
			WebsocketHelper::xor_buffer(frame.data() + header_length, length, mMaskingKey);
		}
		raw_send(frame.data(), header_length + length);
	}

	bool SessionImpl::is_websocket() {
		return mIsWebsocket;
	}

    void SessionImpl::handle_tcpdata()
    {
        bool err = false;
        std::vector<WsMsg> msgs;
        while(1){
            std::string single_raw_msg = mTcpDataUnpack(mData,err);
            if(err){
                break;
            }else{
                msgs.push_back({SocketOpcode::kTcpMsg,single_raw_msg});
                mData = mData.substr(single_raw_msg.length());
            }
        }

        for(auto&it:msgs){
            this->mSessionPtr->publish(on_msg_event{it.opcode,it.data});
        }

        if(err){
            mSessionPtr->publish(on_error_event{"handle_tcpdata error",-1});
            close();
        }
    }

    void SessionImpl::set_tcpmsg_spliter(std::function<std::string(std::string& data,bool &err)> f)
    {
        mTcpDataUnpack = f;
    }
} // namespace uvw
