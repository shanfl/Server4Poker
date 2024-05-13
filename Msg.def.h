#pragma once
#include <inttypes.h>
#include <string>
#include <google/protobuf/message_lite.h>
enum CompressMethod
{
    CM_NONE,
    CM_ZIP,
};

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



using ProtoMsgLite = google::protobuf::MessageLite;


class Message
{   

public:
    static Message Decode(std::string data);
    static std::string Encode(uint32_t msg_id,std::string str,int cm = 0,std::string cookie = "");

    std::string Encode(std::string data);

    //std::dynamic_pointer_cast
    template<typename T>
    std::shared_ptr<T> GetProtoMsg(){ 
        return std::dynamic_pointer_cast<T>(proto_msg);
    };

    void SetProtoPtr(std::shared_ptr<ProtoMsgLite> ptr){
        proto_msg = ptr;
    }
    
    uint32_t MsgId(){
        return mHeader.msg_id;
    }
protected:
    std::shared_ptr<ProtoMsgLite> proto_msg;
private:
    MsgHeader mHeader;
    std::string mCookie;
};
} // namespace Base











