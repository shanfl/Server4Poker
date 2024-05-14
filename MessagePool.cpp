#pragma once
#include <mutex>
#include "Msg.def.h"
#include "MessagePool.h"
namespace Base
{

    void MessagePool::push(Message&msg)
    {
        std::lock_guard<std::mutex> lk(mMutex);
        mVecs.emplace_back(msg);
    }

    std::vector<Message> MessagePool::get(int cnt)
    {
        std::vector<Message> ret;
        if(cnt <= 0) return ret;

        std::lock_guard<std::mutex> lk(mMutex);
        if(cnt <= mVecs.size()){
            ret.assign(mVecs.begin(),mVecs.begin()+cnt);
            for(int i = 0;i < cnt;i++)
            {
                mVecs.erase(mVecs.begin());
            }
            mVecs.shrink_to_fit();
            //
        }else{
            ret = mVecs;
            mVecs.clear();
            mVecs.shrink_to_fit();
        }
    }

    bool MessagePool::get(Message&msg)
    {
        std::lock_guard<std::mutex> lk(mMutex);
        if(mVecs.size() == 0) return false;
        msg = mVecs[0];
        mVecs.erase(mVecs.begin());
        mVecs.shrink_to_fit();
        return true;
    }
}
