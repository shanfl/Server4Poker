#pragma once
#include <mutex>
#include <vector>
#include "Msg.def.h"
namespace Base
{
class MessagePool
{
public:
    void push(Message&msg);
    std::vector<Message> get(int cnt);
    bool get(Message&msg);
private:
    std::vector<Message> mVecs;
    std::mutex mMutex;
};
}
