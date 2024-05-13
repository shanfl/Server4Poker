#include "Thread.hpp"
namespace Base{


Thread::Thread(ServerBase*baseserver)
{
    mThd = thread(Thread::on_work,this);
}
        void Thread::Push()
        {

        }
        void std::vector<Message> Thread::Get(int maxnum)
        {

        }

        static void Thread::on_work(Thread*ptr)
        {
            ptr->msg_loop();
        }
        void Thread::on_msg(Message& msg)
        {

        }

        void Thread::msg_loop(){

        }
}