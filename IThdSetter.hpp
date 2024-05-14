#pragma once

#include "Msg.def.h"
namespace Base {
    
class IThdSetter
{
public:
    virtual int index_want(Message&msg) = 0;

};
}
