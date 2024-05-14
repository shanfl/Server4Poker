#pragma once
#include <inttypes.h>
#include <string>
#include <memory>
//#include <google/protobuf/message_lite.h>
enum CompressMethod
{
    CM_NONE,
    CM_ZIP,
};

namespace google {
namespace protobuf {
    class MessageLite;
}
}

using ProtoMsg = google::protobuf::MessageLite;

namespace Base{


#pragma pack(1)
    struct MsgHeader
    {
        char flags[8]               = {'%','$','%','^'};
        int8_t cm                   = 0;
        uint32_t msg_id             = 0;
        uint32_t msg_len            = 0;
        uint16_t cookie_len         = 0;    
    };
#pragma pack()


class Message
{   

public:
    static Message Decode(std::string data);
    static std::string Encode(uint32_t msg_id,std::string str,int cm = 0,std::string cookie = "");

    std::string Encode(std::string data);

    //std::dynamic_pointer_cast
    template<typename T>
    std::shared_ptr<T> GetProtoMsg();

    void SetProtoPtr(std::shared_ptr<ProtoMsg> ptr);
    
    uint32_t MsgId();
protected:
    std::shared_ptr<ProtoMsg> proto_msg;
private:
    MsgHeader mHeader;
    std::string mCookie;
};
} // namespace Base











