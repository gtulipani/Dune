#ifndef __COMMONS_THREAD_H__
#define __COMMONS_THREAD_H__

#include <thread>

class Thread {
    private:
    std::thread thread;
    bool is_on;
 
    protected:
    virtual void terminate();

    virtual void run() = 0;

    public:
    Thread();

    void start();

    void join();

    bool isRunning() const;

    void stop();

    virtual ~Thread();

    Thread(Thread&& other);
    
    Thread& operator=(Thread&& other);
    
    Thread(const Thread&) = delete;
    Thread& operator=(const Thread&) = delete;
};

#endif // __COMMONS_THREAD_H__
