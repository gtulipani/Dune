#ifndef __BLOCKING_QUEUE_H__
#define __BLOCKING_QUEUE_H__

// STL Libraries
#include <queue>
#include <list>
#include <condition_variable>

template<typename T>
class BlockingQueue {
private:
    std::queue<T> queue;
    std::mutex& mutex;
    std::condition_variable cond;

    typedef std::lock_guard<std::mutex> lock;
    typedef std::unique_lock<std::mutex> ulock;

public:
    explicit BlockingQueue(std::mutex& mutex) : mutex(mutex) {}

    void push(T const &val) {
        lock l(mutex);
        bool wake = queue.empty();
        queue.push(val);
        if (wake) {
            cond.notify_one();
        }
    }

    T pop() {
        ulock u(mutex);
        while (queue.empty()) {
            cond.wait(u);
        }
        T value = queue.front();
        queue.pop();
        return value;
    }

    std::list<T> popAll() {
        ulock u(mutex);
        std::list<T> list;
        while (queue.empty()) {
            cond.wait(u);
        }
        while (!queue.empty()) {
            list.push_back(queue.front());
            queue.pop();
        }
        return list;
    }
};


#endif //__BLOCKING_QUEUE_H__
