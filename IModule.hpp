#pragma once
#include "Msg.def.h"
namespace Base 
{
    class IModule
    {
    public:
        virtual bool is_accpeted(Message&msg) = 0;

        virtual int idx_thd_wanted(Message&msg);

        virtual int idx_mod() = 0;

        virtual bool init() = 0;

        virtual void on_msg(Message&msg) = 0;
    };
}

