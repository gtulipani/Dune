#ifndef __PRIORITY_QUEUE_H__
#define __PRIORITY_QUEUE_H__

#include <vector>
#include <utility>

template<typename T>
class PriorityQueue {
    private:
    int top_pos;
    std::vector<std::pair<T, int>> vec;

    unsigned int find_top() const {
        unsigned int pos = 0;
        unsigned int n = vec.size();
        for (unsigned int i = 0; i < n; i++) {
            if (vec.at(i).second < vec.at(pos).second) {
                pos = i;
            }
        }
        return pos;
    }

    public:
    PriorityQueue() {
        top_pos = -1;
    }

    bool empty() const {
        return size() == 0;
    }

    unsigned int size() const {
        return vec.size();
    }

    void push(const T& element, int priority) {
        vec.emplace_back(element, priority);
        top_pos = -1;
    }

    T& top() {
        if (top_pos >= 0) return vec.at(top_pos).first;

        top_pos = find_top();
        return vec.at(top_pos).first;
    }

    const T& top() const {
        if (top_pos >= 0) return vec.at(top_pos).first;

        top_pos = find_top();
        return vec.at(top_pos).first;
    }

    void pop() {
        unsigned int i = top_pos >= 0 ? top_pos : find_top();
        top_pos = -1;
        vec.erase(vec.begin() + i);
    }
};

#endif
