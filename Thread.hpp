#pragma once;

namespace Base
{   
    class ServerBase;


    class Thread
    {   
    public:
    
        Thread(ServerBase*baseserver);
        void Push();
        void std::vector<Message> Get(int maxnum);
        static void on_work(Thread*ptr);
        void on_msg(Message& msg);
    private:
        int mIndex;    
    };
}   // namespace Base
