#ifndef __SHAQUE_H__
#define __SHAQUE_H__

#include <queue>
#include <list>
#include "../../commons/Lock.h"

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

    std::list<T> popAll() {
        Lock l(m);
        std::list<T> list;
        while (!queue.empty()) {
            list.push_front(queue.front());
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
