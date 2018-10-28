#include "Thread.h" 

Thread::Thread() {
    is_on = false;
}

void Thread::start() {
    if (is_on) return;
    is_on = true;
    thread = std::thread(&Thread::run, this);
}

void Thread::join() {
    thread.join();
}

bool Thread::isRunning() const {
    return is_on;
}

void Thread::stop() {
    is_on = false;
    terminate();
}

void Thread::terminate() {}

Thread::~Thread() {
    if (this->isRunning()) this->stop();
}

Thread::Thread(Thread&& other) {
    this->thread = std::move(other.thread);
}

Thread& Thread::operator=(Thread&& other) {
    this->thread = std::move(other.thread);
    return *this;
}
