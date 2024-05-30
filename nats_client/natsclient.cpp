#include "natsclient.hpp"
#include <map>
#include <iostream>
#include "cJSON.h"
#include <assert.h>


namespace uvw {

    //uint64_t nats_client::id_unique = 0;

    static const std::string CLRF = "\r\n";


    std::map<std::string,int> starter_config  = {
        {"INFO",1},
        {"MSG ",2},
        {"PING",1},
        {"PONG",1},
        {"+OK ",1},
        {"-ERR",1}
    };


    void Stringsplit(const std::string& str, const char split, std::vector<std::string>& res)
    {
        if (str == "")		return;
        //在字符串末尾也加入分隔符，方便截取最后一段
        std::string strs = str + split;
        size_t pos = strs.find(split);

        // 若找不到内容则字符串搜索函数返回 npos
        while (pos != strs.npos)
        {
            std::string temp = strs.substr(0, pos);
            res.push_back(temp);
            //去掉已分割的字符串,在剩下的字符串中进行分割
            strs = strs.substr(pos + 1, strs.size());
            pos = strs.find(split);
        }
    }



    bool StartWith(std::string&str,std::string &starter)
    {
        if(str.size() < starter.size()) return false;
        for(int i = 0;i < starter.size();i++)
            if(str[i] != starter[i])
                return  false;;
        return true;
    }

    std::string json_get(cJSON * json,std::string key){
        auto*name = cJSON_GetObjectItemCaseSensitive(json, key.c_str());
        if(cJSON_IsString(name) && name->valuestring != nullptr){
            return std::string(name->valuestring);
        }
        return "";
    }

    bool json_get_bool(cJSON* json,std::string key){
        auto*name = cJSON_GetObjectItemCaseSensitive(json, key.c_str());
        if(cJSON_IsBool(name)){
            return cJSON_IsTrue(name);
        }
        return false;
    }

    int json_get_int(cJSON * json,std::string key){
        auto*name = cJSON_GetObjectItemCaseSensitive(json, key.c_str());
        if(cJSON_IsNumber(name)){
            return name->valuedouble;
        }
        return 0;
    }

    void json_get_vecstring(cJSON*json,std::string key,std::vector<std::string> & vget)
    {
        const cJSON *resolution = NULL;
        auto* resolutions = cJSON_GetObjectItemCaseSensitive(json, "resolutions");
        cJSON_ArrayForEach(resolution, resolutions)
        {
            if(cJSON_IsString(resolution) && resolution->valuestring!= nullptr)
                vget.push_back(std::string(resolution->valuestring));
        }
    }


    std::shared_ptr<info_data> info_parser(std::string &jsondata)
    {
        //std::shared_ptr<info_data> infoPtr= std::make_shared<info_data>();
        //std::clog << "INFO:" << jsondata << "\n";
        cJSON *monitor_json = cJSON_Parse(jsondata.c_str());
        std::shared_ptr<info_data> infoPtr= std::make_shared<info_data>();
        infoPtr->t = INFO;
        infoPtr->server_id      = json_get(monitor_json, "server_id");
        infoPtr->server_name    = json_get(monitor_json, "server_name");
        infoPtr->go             = json_get(monitor_json, "go");
        infoPtr->host           = json_get(monitor_json, "host");
        infoPtr->port           = json_get(monitor_json, "port");
        infoPtr->headers        = json_get_bool(monitor_json,"headers");
        infoPtr->max_payload    = json_get_int(monitor_json,"max_payload");
        infoPtr->proto          = json_get_int(monitor_json,"proto");
        infoPtr->client_id      = json_get_int(monitor_json,"client_id");
        infoPtr->auth_required  = json_get_bool(monitor_json,"auth_required");

        infoPtr->tls_required   = json_get_bool(monitor_json,"tls_required");
        infoPtr->tls_verify     = json_get_bool(monitor_json,"tls_verify");
        infoPtr->tls_available  = json_get_bool(monitor_json,"tls_available");
        json_get_vecstring(monitor_json,"connect_urls",infoPtr->connect_urls);
        json_get_vecstring(monitor_json,"ws_connect_urls",infoPtr->ws_connect_urls);

        infoPtr->ldm            = json_get_bool(monitor_json,"ldm");
        infoPtr->git_commit     = json_get(monitor_json, "git_commit");
        infoPtr->jetstream      = json_get_bool(monitor_json,"jetstream");
        infoPtr->ip             = json_get(monitor_json, "ip");
        infoPtr->client_ip      = json_get(monitor_json, "client_ip");
        infoPtr->nonce          = json_get(monitor_json, "nonce");
        infoPtr->cluster        = json_get(monitor_json, "cluster");
        infoPtr->domain         = json_get(monitor_json, "domain");
        cJSON_Delete(monitor_json);
        return infoPtr;
    }

    std::shared_ptr<data_base> Split2Spec(std::string data,std::string starter,int nclrf,std::vector<int> pos)
    {
        //INFO {"option_name":option_value,...}␍␊
        if(starter == "INFO"){
            std::string jsondata = data.substr(5,pos[0]);
            //std::clog << "INFO:" << jsondata << "\n";
            //cJSON *monitor_json = cJSON_Parse(jsondata.c_str());
            std::shared_ptr<info_data> infoPtr= info_parser(jsondata);
            return infoPtr;
        }else if(starter == "MSG "){
            //MSG <subject> <sid> [reply-to] <#bytes>␍␊[payload]␍␊
            assert(pos.size() == 2);
            std::shared_ptr<msg_data> msgPtr= std::make_shared<msg_data>();
            msgPtr->t = MSG;
            std::string dataPre = data.substr(0,pos[1]);
//            std::string payload = data.substr(pos[1]+2);
            msgPtr->payload = data.substr(pos[1]+2);
            std::vector<std::string> v;
            Stringsplit(dataPre,' ',v);
            if(v.size() == 5){
                msgPtr->subject = v[1];
                msgPtr->sid = v[2];
                msgPtr->reply_to = v[3];
                msgPtr->bytes_len = std::atoi(v[4].c_str());

            }else if(v.size() == 4)
            {
                msgPtr->subject = v[1];
                msgPtr->sid = v[2];
                 msgPtr->bytes_len = std::atoi(v[3].c_str());
            }
            else {
                msgPtr = nullptr;
            }
            return msgPtr;
        }else if(starter == "PING"){
            std::shared_ptr<ping_data> ping = std::make_shared<ping_data>();
            ping->t = PING;
            return ping;
        }else if(starter == "PONG")
        {
            std::shared_ptr<pong_data> pong = std::make_shared<pong_data>();
            pong->t = PONG;
            return pong;
        }else if(starter == "+OK ")
        {
            std::shared_ptr<ok_data> ok = std::make_shared<ok_data>();
            ok->t = OK;
            return ok;

        }else if(starter == "-ERR"){
            std::shared_ptr<err_data> errPtr = std::make_shared<err_data>();
            errPtr->t = ERR;
            int posSpace = data.find_first_of(' ');
            if(posSpace == std::string::npos) return nullptr;
            errPtr->err_msg = data.substr(posSpace+1,pos[0]);
            return errPtr;
        }else
        {
            std::clog << "not implement !!!!!!!!!11\n";
            return nullptr;
        }
    }

    std::vector<std::shared_ptr<data_base>> Parser(std::string&data,bool&err)
    {
        err = false;
        if(data.size() < 4) return std::vector<std::shared_ptr<data_base>>();
        std::vector<std::shared_ptr<data_base>> ret;
        std::string fit_starter;
        int nCLRF = 0;

        while(data.size() > 4){
            std::string test = std::string(data.c_str(),4);

            if(starter_config.find(test) == starter_config.end())
            {
                err = true;
                return ret;
            }

            fit_starter =test;
            nCLRF = starter_config[test];

            int pos = 0;
            int i = 0;
            std::vector<int>posV;

            for(i = 0;i < nCLRF;i++){
                pos = data.find_first_of(CLRF,pos);
                if(pos == std::string::npos)
                    break;
                else
                {
                    posV.push_back(pos);
                }
            }

            if(i < nCLRF || pos == std::string::npos){
                break;
            }else{
                std::string msg_data = data.substr(0,pos);
                std::shared_ptr<data_base> spec_msgptr = Split2Spec(msg_data,fit_starter,nCLRF,posV);
                ret.push_back(spec_msgptr);
                data = data.substr(pos+CLRF.length());
            }
        }
        return ret;
    }

    nats_client::nats_client(uvw::loop::token token, std::shared_ptr<uvw::loop> parent,int centerid,int mathineid):uvw::resource<uvw::nats_client,natsclient_t,
                        info_event_nats,
                        msg_event_nats,ping_event_nats,pong_event_nats,ok_event_nats,error_event_nats>(token,parent){
        //mTcpHanle = parent->resource<uvw::tcp_handle>();

        mSnowFlake.init(centerid,mathineid);

        mAsync = parent->resource<uvw::async_handle>();
        mAsync->on<uvw::async_event>([this](const auto&e,const auto&h){
            std::lock_guard<std::mutex> lk(mMutexOpQueue);
            for(auto&it:mOpQueue){
                switch (it.opcode) {
                    case CONNECT:
                    {
                        _connect(std::get<0>(it.connect),std::get<1>(it.connect));
                        this->mKeepConnect = std::get<2>(it.connect);
                    }
                    break;
                    case DISCONNECT:
                    {
                        _disconnect();
                        this->mKeepConnect = false;
                    }
                    break;
                    case RECONNECT:
                    {
                        _connect(this->mHost,this->mPort);
                    }
                    break;
                    case SEND:
                    {
                        _raw_send(it.data_send);
                    }
                    break;
                    default:
                        std::clog<< " error,need to check opcode :" << it.opcode  << std::endl;
                }
            }
            mOpQueue.clear();
        });
#if 0
        mTimerReconnect = parent->resource<uvw::timer_handle>();
        mTimerReconnect->on<uvw::timer_event>([this](const auto&,const auto&){
            if(!mKeepConnect) return;
            if(getState() == NONE || getState() == CLOSED)
            {
                _connect(this->mHost,this->mPort);
            }
        });
#endif
    }

    void nats_client::connect(std::string host,int port,bool keep)
    {
        if(this->mUvMainThdId != std::this_thread::get_id())
        {
            std::lock_guard<std::mutex> lk(mMutexOpQueue);
            mOpQueue.push_back({OpcodeAsync::CONNECT,{host,port,keep}});
            mAsync->send();
        }else{
            this->mHost = host;
            this->mPort = port;
            mKeepConnect = keep;
            int ret = _connect(host,port);
            std::clog << "con-ret:" << ret << std::endl;
        }
    }

    void nats_client::disconnect()
    {
        if(this->mUvMainThdId != std::this_thread::get_id())
        {
            std::lock_guard<std::mutex> lk(mMutexOpQueue);
            mOpQueue.push_back({OpcodeAsync::DISCONNECT});
            mAsync->send();
        }else{
            _disconnect();
            this->mKeepConnect = false;
        }
    }

    int nats_client::_connect(std::string host,int port)
    {
        this->mHost = host;
        this->mPort = port;

        if(mTcpHanle){
            mTcpHanle->reset();
            mTcpHanle->close();
            mTcpHanle = nullptr;
            mData= "";
            mSidSubjectsMap.clear();
            mReqestMap.clear();
        }
        mTcpHanle = this->parent().resource<uvw::tcp_handle>();
        mTcpHanle->on<data_event>([this](const auto&e,const auto&h){
            mData += std::string(e.data.get(),e.length);
            std::cout << mData << std::endl;
            bool err = false;
            std::vector<std::shared_ptr<data_base>> msgVecs = Parser(mData,err);

            if(err){
                std::cout << "parser error!" << std::endl;
                _disconnect();
                return;
            }

            for(auto&it:msgVecs){
                if(it == nullptr){
                    _disconnect();
                    return;
                }

                switch (it->t) {
                case INFO:
                {
                    info_data data = *std::dynamic_pointer_cast<info_data>(it);
                    info_event_nats ev {data};
                    this->publish(ev);
                }
                    break;
                case MSG:
                    //this->publish(msg_event_nats{*std::dynamic_pointer_cast<msg_data>(it)});
                    {
                        msg_data data = *std::dynamic_pointer_cast<msg_data>(it);
                        std::string sid = data.sid;
                        if(mReqestMap.find(sid) != mReqestMap.end()){
                            mReqestMap[sid].cb(this->shared_from_this(),
                            data.subject,
                            data.payload,
                            data.reply_to,false);
                            mReqestMap.erase(sid);
                        }else if(mSidSubjectsMap.find(sid) != mSidSubjectsMap.end()){
                            if(mSubjectCallback){
                                mSubjectCallback(this->shared_from_this(),
                                data.subject,
                                data.payload,
                                data.reply_to,false);
                            }
                        }else{
                            std::clog << data.subject << " not handle" <<std::endl;
                        }
                    }
                    break;
                case PING:
                    //this->pong();
                    this->publish(ping_event_nats{*std::dynamic_pointer_cast<ping_data>(it)});
                    break;
                case PONG:
                    this->publish(pong_event_nats{*std::dynamic_pointer_cast<pong_data>(it)});
                    break;
                case OK:
                    this->publish(ok_event_nats{*std::dynamic_pointer_cast<ok_data>(it)});
                    break;
                case ERR:
                    this->publish(error_event_nats{*std::dynamic_pointer_cast<err_data>(it)});
                    //disconnect();
                    break;
                default:
                    std::clog << "err!\n";
                    _disconnect();
                    break;
                }
            }
        });

        mTcpHanle->on<connect_event>([this](const auto&e,const auto&h){
            std::clog << "connected\n";
            setState(uvw::NatsState::CONNECTED);
            mTcpHanle->read();
        });

        mTcpHanle->on<error_event>([this](const error_event&e,const auto&h){
            std::clog << "error_event:" << e.what() << ",state:" << (int)getState() <<  std::endl;
            if(getState() == uvw::NatsState::CONNECTING){
                setState(uvw::NatsState::CLOSED);
                _reconnect_delay(2000);
            }
        });

        mTcpHanle->on<close_event>([this](const auto&e,const auto&h){
            std::clog << "close_event\n";
            setState(uvw::NatsState::CLOSED);
            if(this->mKeepConnect){
                _reconnect_delay(2000);
            }
        });

        setState(uvw::NatsState::CONNECTING);
        return mTcpHanle->connect(host,port);
    }

    void nats_client::_disconnect()
    {
        if(getState() == NatsState::CONNECTED || getState() == NatsState::CONNECTING)
        {
            mTcpHanle->close();
            setState(NatsState::CLOSING);
        }            
    }

    void nats_client::setState(NatsState state)
    {
        mState = state;
    }
    uvw::NatsState nats_client::getState(){
        return mState;
    }

    void nats_client::_raw_send(const char*data,size_t len)
    {
        mTcpHanle->write((char*)data,len);
    }

    void nats_client::_raw_send(std::string&str)
    {
        _raw_send(str.c_str(),str.length());
    }

    void nats_client::raw_send(std::string&str)
    {
        raw_send(str.c_str(),str.length());
    }

    void nats_client::raw_send(const char*data,size_t len)
    {
        if(this->mUvMainThdId != std::this_thread::get_id()){
            std::lock_guard<std::mutex> lk(mMutexOpQueue);
            mOpQueue.push_back({OpcodeAsync::SEND,{"",0,0},std::string(data,len)});
            mAsync->send();
        }else{
            _raw_send(data,len);
        }
    }

    void nats_client::ping()
    {
        std::string ping = "PING"+CLRF;
        raw_send(ping.c_str(),ping.length());
    }

    void nats_client::pong()
    {
        std::string ping = "PONG"+CLRF;
        raw_send(ping.c_str(),ping.length());
    }

    void nats_client::sub(std::string subject)
    {
        sub(subject,next_sid());
    }

    void nats_client::sub(std::string subject,std::string sid)
    {
        std::string a = str_sub(subject,sid);
        mSidSubjectsMap[sid] = std::make_pair(subject,"");
        raw_send(a);
    }

    std::string nats_client::str_sub(std::string subject,std::string sid)
    {
        std::string a = "SUB " + subject+" " + sid + CLRF;
        return a;
    }

    void nats_client::sub_with_queuegruop(std::string subject,std::string queue_group)
    {
        sub_with_queuegroup(subject,next_sid(),queue_group);
    }

    void nats_client::sub_with_queuegroup(std::string subject,std::string sid,std::string queue_group)
    {
        std::string a ="SUB " + subject + " " + queue_group + " " + sid + CLRF;        
        raw_send(a);
    }

    void nats_client::unsub(std::string sid,int max_msgs)
    {
        if(max_msgs > 0){
            std::string a ="UNSUB " + sid + " " + std::to_string(max_msgs) + CLRF;
            raw_send(a);
        }else{
            std::string a ="UNSUB " + sid + CLRF;
            raw_send(a);
        }
    }

    void nats_client::pub(std::string subject,std::string msg)
    {
        std::string a = "PUB " + subject + " " + std::to_string(msg.length()) + CLRF + msg + CLRF;
        raw_send(a);
    }

    void nats_client::pub_with_reply(std::string subject,std::string msg,std::string replay_to)
    {
        assert(replay_to.length() > 0);
        std::string a = "PUB " + subject + " " + replay_to +" " + std::to_string(msg.length()) + CLRF + msg + CLRF;
        raw_send(a);
    }

    std::string nats_client::request_reply(std::string subject,std::string msg,
                 NATS_CALLBACK cb,std::chrono::microseconds timeout)
    {
        std::string sid = next_sid();
        std::string subject_reply_to = "reply_to" + sid;
        sub(subject_reply_to,sid);
        unsub(sid,1);
        pub_with_reply(subject,msg,subject_reply_to);
        mReqestMap[sid]  = Request(subject,subject_reply_to,sid,timeout,cb);
        return subject_reply_to;
    }

    void nats_client::send_connect_data(connect_data data)
    {
        cJSON *monitor = cJSON_CreateObject();
        cJSON_AddBoolToObject(monitor,"verbose",data.verbose);
        cJSON_AddBoolToObject(monitor,"pedantic",data.pedantic);
        cJSON_AddBoolToObject(monitor,"tls_required",data.tls_required);
        cJSON_AddStringToObject(monitor,"auth_token",data.auth_token.c_str());

        cJSON_AddStringToObject(monitor,"user",data.user.c_str());
        cJSON_AddStringToObject(monitor,"pass",data.pass.c_str());
        cJSON_AddStringToObject(monitor,"name",data.name.c_str());
        cJSON_AddStringToObject(monitor,"lang",data.lang.c_str());
        cJSON_AddStringToObject(monitor,"version",data.version.c_str());

        cJSON_AddNumberToObject(monitor,"protocol",data.protocol);
        cJSON_AddBoolToObject(monitor,"echo",data.echo);

        cJSON_AddStringToObject(monitor,"sig",data.sig.c_str());
        cJSON_AddStringToObject(monitor,"jwt",data.jwt.c_str());

        cJSON_AddBoolToObject(monitor,"no_responders",data.no_responders);
        cJSON_AddBoolToObject(monitor,"headers",data.headers);

        cJSON_AddStringToObject(monitor,"nkey",data.nkey.c_str());

        std::string data_jsoned ="CONNECT " +  std::string(cJSON_Print(monitor)) + CLRF;
        cJSON_Delete(monitor);

        raw_send(data_jsoned);
    }

    void nats_client::send_connect_str(std::string str)
    {
        std::string full = "CONNECT " + str + CLRF;
        raw_send(full);
    }

    void nats_client::_reconnect_delay(int ms)
    {
        if(mTimerReconnect){
            mTimerReconnect->reset();
            mTimerReconnect->stop();
            mTimerReconnect = nullptr;
        }
        mTimerReconnect = this->parent().resource<uvw::timer_handle>();
        mTimerReconnect->on<uvw::timer_event>([this,ms](const auto&,const auto&){
            _connect(this->mHost,this->mPort);
        });
        mTimerReconnect->start(uvw::timer_handle::time{ms},uvw::timer_handle::time{0});
    }

    std::string nats_client::next_sid()
    {
        return std::to_string(mSnowFlake.nextid()) + std::to_string((long long)mTcpHanle.get());
    }

    void nats_client::set_sub_callback(NATS_CALLBACK cb) {
        mSubjectCallback = cb;
    }

    void nats_client::set_uv_thdid(std::thread::id id){
        mUvMainThdId = id;
    }
}

