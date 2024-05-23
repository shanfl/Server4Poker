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

std::string Message::z_compress(std::string &str,bool &err)
{
    err = false;
    mz_ulong sz_com = mz_compressBound(str.length());

    mz_uint8* buf = (unsigned char*)malloc(sz_com);
    memset(buf,'\0',sz_com);

    int res = mz_compress(buf,&sz_com,(const unsigned char*)str.c_str(),str.length());
    if(res != MZ_OK){
        err = true;
        return "";
    }
    std::string ret((char*)buf,sz_com);
    free(buf);
    return ret;
}


std::string Message::z_uncompress(std::string &str,size_t uncompress_len,bool&err)
{
    std::cout << "uncompress_len:" << uncompress_len <<std::endl;
    err = false;
    std::string ret(uncompress_len,'\0');
    //std::cout << "ret-len:" << ret.length() << std::endl;
    mz_ulong len = (mz_ulong)uncompress_len;
    int res = mz_uncompress((unsigned char*)ret.data(),&len,(const unsigned char*)str.c_str(),str.length());
    if(res != MZ_OK){
        err = true;
        return "";
    }
    return ret;
}


    std::string Message::fast_split(std::string& data,bool &err)
    {
        err = false;
        if(data.length() < HEADER_LEN) return "";
        MsgHeader hdr;
        memcpy((char*)&hdr,data.c_str(),HEADER_LEN);
        hdr.msg_id              = ntohl(hdr.msg_id);
        hdr.msg_len             = ntohl(hdr.msg_len);
        hdr.msg_unpack_len      = ntohl(hdr.msg_unpack_len);
        hdr.cookie_len          = ntohs(hdr.cookie_len);

        if(data.length() < hdr.msg_len + hdr.cookie_len + HEADER_LEN)
            return "";

        if(std::string(hdr.flags,8) != header_flags)
        {
            err = true;
            return "";
        }

        std::string ret = data.substr(0,hdr.msg_len + hdr.cookie_len + HEADER_LEN);
        data = data.substr(hdr.msg_len + hdr.cookie_len + HEADER_LEN);
        return ret;
    }

    bool Message::Decode(std::string&data,MsgHeader&hdr,std::string&body)
    {
        if(data.length() < HEADER_LEN) return false;
        memcpy((char*)&hdr,data.c_str(),HEADER_LEN);
        hdr.msg_id          =   ntohl(hdr.msg_id);
        hdr.msg_len         =   ntohl(hdr.msg_len);
        hdr.msg_unpack_len  =   ntohl(hdr.msg_unpack_len);
        hdr.cookie_len      =   ntohs(hdr.cookie_len);

        if(data.length() != hdr.msg_len + hdr.cookie_len + HEADER_LEN)
            return false;

        hdr.cookie      =   std::string(data.c_str()+HEADER_LEN,hdr.cookie_len);
        body = std::string(data.c_str()+HEADER_LEN + hdr.cookie_len,hdr.msg_len);


        if(hdr.cm == CompressMethod::CM_ZIP){
            bool err = false;
            body = z_uncompress(body,hdr.msg_unpack_len,err);
            return err;
        }
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



    bool Message::parser(std::string &data)
    {
        return this->proto_msg->ParseFromString(data);
    }

    std::string Message::Encode(uint32_t msg_id,std::string str,std::string cookie)
    {
        CompressMethod cm = CompressMethod::CM_NONE;
        uint32_t unpack_body_len = str.length();
        //uint32_t body_len = unpack_body_len;

        if(str.length() > 5*1024){
            cm = CompressMethod::CM_ZIP;
            bool err = false;
            str = z_compress(str,err);
            if(err)
                return "";
        }

        int len = HEADER_LEN + cookie.length()+ str.length();

        std::string ret;
        MsgRawHeader hdr;
        hdr.cm = cm;
        hdr.msg_id = htonl(msg_id);
        hdr.msg_len = htonl(str.length());
        hdr.msg_unpack_len = htonl(unpack_body_len);
        hdr.cookie_len = htonl(cookie.length());

        ret.append((char*)&hdr,HEADER_LEN);
        ret.append(cookie);
        ret.append(str);
        assert(len = ret.length());
        return ret;
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











