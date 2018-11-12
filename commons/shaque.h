#ifndef __SHAQUE_H__
#define __SHAQUE_H__

// STL Libraries
#include <queue>
#include <list>

// Commons Libraries
#include "Lock.h"

template<typename T>
class shaque {
    std::queue<T> queue;
    std::mutex& m;

    public:
    explicit shaque(std::mutex& _m) : m(_m) {}

    void push(const T& value) {
        Lock l(m);
        queue.push(value);
    }

    void push(const std::vector<T>& values) {
        Lock l(m);
        queue.push(values);
    }

    T pop() {
        Lock l(m);
        T value = queue.front();
        queue.pop();
        return value;
    }

    std::list<T> popAll() {
        Lock l(m);
        std::list<T> list;
        while (!queue.empty()) {
            list.push_back(queue.front());
            queue.pop();
        }
        return list;
    }

    bool empty() const {
        return queue.empty();
    }

    unsigned int size() const {
        return queue.size();
    }
};

#endif // __SHAQUE_H__
