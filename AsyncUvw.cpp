#include "AsyncUvw.hpp"
#include "ServerBase.h"
namespace Base
{
    AsyncUvw::AsyncUvw(ServerBase*base){
          mAsync = base->loop()->resource<uvw::async_handle>();

          mAsync->on<uvw::async_event>([this](const auto& ev, const auto& hdl) {
              if(this->mFn){
                  this->mFn();
              }
          });
    }

    std::shared_ptr<uvw::async_handle> mAsync;

    void AsyncUvw::set_do_fn(std::function<void(void)> fn)
    {
      mFn = fn;
    }

    void AsyncUvw::do_sync(){
      mAsync->send();
    }
}
