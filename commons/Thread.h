#ifndef __COMMONS_THREAD_H__
#define __COMMONS_THREAD_H__

#include <thread>

class Thread {
    private:
    std::thread thread;
 
    public:
    Thread();

    void start();

    void join();

    virtual void run() = 0;

    virtual void stop() = 0;

    virtual bool hasFinished() const = 0;

    virtual ~Thread();

    Thread(Thread&& other);
    
    Thread& operator=(Thread&& other);
    
    Thread(const Thread&) = delete;
    Thread& operator=(const Thread&) = delete;
};

#endif // __COMMONS_THREAD_H__
