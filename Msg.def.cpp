#pragma once
#include <inttypes.h>
#include <string>
#include "Msg.def.h"
#include <google/protobuf/message_lite.h>
#include "miniz/miniz.h"
#ifdef _WIN32

#else
#include <arpa/inet.h>
#endif

//using ProtoMsgLite = google::protobuf::MessageLite;

namespace Base{

    std::string Message::z_compress(std::string &str,bool&err)
    {
        mz_compressBound
    }

    std::string Message::z_uncompress(std::string&str,bool&err)
    {

    }


    std::string fast_split(std::string& data,bool &err){
        err = false;
        if(data.length() < HEADER_LEN) return "";
        MsgHeader hdr;
        memcpy((char*)&hdr,data.c_str(),HEADER_LEN);
        hdr.msg_id      =   ntohl(hdr.msg_id);
        hdr.msg_len     =   ntohl(hdr.msg_len);
        hdr.cookie_len  =   ntohs(hdr.cookie_len);

        if(data.length() < hdr.msg_len + hdr.cookie_len + HEADER_LEN)
            return "";

        if(std::string(hdr.flags,8) != flags)
        {
            err = true;
            return "";
        }

        std::string ret = data.substr(0,hdr.msg_len + hdr.cookie_len + HEADER_LEN);
        data = data.substr(hdr.msg_len + hdr.cookie_len + HEADER_LEN);
        return ret;
    }

    bool Decode(std::string&data,MsgHeader&hdr,std::string&body)
    {
        if(data.length() < HEADER_LEN) return false;
        memcpy((char*)&hdr,data.c_str(),HEADER_LEN);
        hdr.msg_id      =   ntohl(hdr.msg_id);
        hdr.msg_len     =   ntohl(hdr.msg_len);
        hdr.cookie_len  =   ntohs(hdr.cookie_len);

        if(data.length() != hdr.msg_len + hdr.cookie_len + HEADER_LEN)
            return false;

        hdr.cookie      =   std::string(data.c_str()+HEADER_LEN,hdr.cookie_len);
        body = std::string(data.c_str()+HEADER_LEN + hdr.cookie_len,hdr.msg_len);
        return true;
        //data = data.substr(HEADER_LEN+hdr.cookie_len+hdr.msg_len);
        return true;
    }



    Message Message::Decode(std::shared_ptr<ProtoMsg> ptr,std::string data,bool&err)
    {
        Message msg;
        //msg.SetProtoPtr(ptr);
        std::string body;
        err = Decode(data,msg.mHeader,body);
        if(!err) return msg;
        err = ptr->ParseFromString(body);
        if(!err) return msg;
        msg.SetProtoPtr(ptr);
        return msg;
    }

    bool Message::Parser(std::string &data)
    {
        return this->proto_msg->ParseFromString(data);
    }

    std::string Message::Encode(uint32_t msg_id,std::string str,int cm,std::string cookie)
    {
        int len = HEADER_LEN + cookie.length()+ str.length();
        std::string ret;
        ret.append(flags);  //


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











