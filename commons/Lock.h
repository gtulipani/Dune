#ifndef __COMMONS_LOCK_H__
#define __COMMONS_LOCK_H__

#include <mutex>

class Lock {
    private:
    std::mutex &m;

    public:
    explicit Lock(std::mutex &m);

    ~Lock();

    Lock(const Lock&) = delete;
    Lock& operator=(const Lock&) = delete;
    Lock(Lock&&) = delete;
    Lock& operator=(Lock&&) = delete;
};

#endif // __COMMONS_LOCK_H__
