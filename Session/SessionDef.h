#ifndef SESSIONDEF_H
#define SESSIONDEF_H
#include <string>
namespace uvw {

    #define FIN			0x80
    #define RSV1		0x40
    #define RSV2		0x20
    #define RSV3		0x10
    #define OPCODE		0X0F
    #define MASK		0x80
    #define PAYLOADLEN  0x7F

    enum SocketOpcode {
        kContinuation = 0,
        kTextFrame = 1,
        kBinaryFrame = 2,
        kClose = 8,
        kPing = 9,
        kPong = 10,

        kMaxWebsocketCode,
        kTcpMsg = kMaxWebsocketCode + 100
    };

    enum class SideClient{
        REMOTE_CLIENT,
        LOCAL_CLIENT
    };


    enum SessionState{
        NONE,
        CONNECTING,
        TCP_CONNECTED,
        PROXY_JUDGING,
        WS_JUDGING,
        CONNECTED,
        CLOSING,
        CLOSED,
    };

    struct WsMsg //rename SessonMsg
    {
        SocketOpcode    opcode;
        std::string     data;
    };
}


#endif // SESSIONDEF_H
