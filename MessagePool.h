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
        void push(T&msg);
        std::vector<T> get(int cnt);
        bool get(T&msg);
    private:
        std::vector<T> mVecs;
        std::mutex mMutex;
    };
}
