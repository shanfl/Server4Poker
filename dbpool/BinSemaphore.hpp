#include <mutex>
#include <condition_variable>

// binary semaphore
class binsem {
public:
    explicit binsem(int init_count = count_max)
      : count_(init_count) {}

    // P-operation / acquire
    void wait()
    {
        std::unique_lock<std::mutex> lk(m_);
        cv_.wait(lk, [=]{ return 0 < count_; });
        --count_;
    }
    bool try_wait()
    {
        std::lock_guard<std::mutex> lk(m_);
        if (0 < count_) {
            --count_;
            return true;
        } else {
            return false;
        }
    }
    // V-operation / release
    void signal()
    {
        std::lock_guard<std::mutex> lk(m_);
        if (count_ < count_max) {
            ++count_;
            cv_.notify_one();
        }
    }

    // Lockable requirements
    void lock() { wait(); }
    bool try_lock() { return try_wait(); }
    void unlock() { signal(); }

private:
    static const int count_max = 1;
    int count_;
    std::mutex m_;
    std::condition_variable cv_;
};

template <int N>
class CounterSema 
{
public:
    explicit CounterSema(int init_count)
        : count_(init_count) {}

    // P-operation / acquire
    void acquire()
    {
        std::unique_lock<std::mutex> lk(m_);
        cv_.wait(lk, [=] { return 0 < count_; });
        --count_;
    }
    bool try_acquire()
    {
        std::lock_guard<std::mutex> lk(m_);
        if (0 < count_) {
            --count_;
            return true;
        }
        else {
            return false;
        }
    }
    // V-operation / release
    void release()
    {
        std::lock_guard<std::mutex> lk(m_);
        if (count_ < count_max) {
            ++count_;
            cv_.notify_one();
        }
    }

    //// Lockable requirements
    //void lock() { acquire(); }
    //bool try_lock() { return try_acquire(); }
    //void unlock() { release(); }

private:
    int count_max = N;
    int count_;
    std::mutex m_;
    std::condition_variable cv_;
};

using BinSemaphore = CounterSema<1>;