#pragma once

#include "uvw.hpp"
#include <memory>
namespace Base {

class ServerBase;
class AsyncUvw
{
public:
    AsyncUvw();
    void init(ServerBase*base);
    std::shared_ptr<uvw::async_handle> mAsync;
    void set_do_fn(std::function<void(void)> fn);
    void do_sync();
    std::function<void(void)> mFn;
};

}
