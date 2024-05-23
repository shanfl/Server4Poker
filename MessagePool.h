#pragma once
#include <mutex>
#include <vector>
#include "Msg.def.h"
namespace Base
{
    template <class T>
    class MessagePool
    {
    public:
        void push(T&msg)
        {
            std::lock_guard<std::mutex> lk(mMutex);
            mVecs.emplace_back(msg);
        }
        std::vector<T> get(int cnt)
        {
            std::vector<T> ret;
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
        bool get(T&msg)
        {
            std::lock_guard<std::mutex> lk(mMutex);
            if(mVecs.size() == 0) return false;
            msg = mVecs[0];
            mVecs.erase(mVecs.begin());
            mVecs.shrink_to_fit();
            return true;
        }
    private:
        std::vector<T> mVecs;
        std::mutex mMutex;
    };
}
