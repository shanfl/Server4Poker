#pragma once
#include <inttypes.h>
#include <string>
#include "Msg.def.h"
#include <google/protobuf/message_lite.h>


//using ProtoMsgLite = google::protobuf::MessageLite;

namespace Base{

    Message Message::Decode(std::string data)
    {

    }

    std::string Message::Encode(uint32_t msg_id,std::string str,int cm  ,std::string cookie)
    {

    }

    std::string Message::Encode(std::string data){

    }

    //std::dynamic_pointer_cast
    template<typename T>
    std::shared_ptr<T> Message::GetProtoMsg(){
        return std::dynamic_pointer_cast<T>(proto_msg);
    };

    void Message::SetProtoPtr(std::shared_ptr<ProtoMsg> ptr){
        proto_msg = ptr;
    }

    uint32_t Message::MsgId(){
        return mHeader.msg_id;
    }

} // namespace Base











