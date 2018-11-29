#ifndef __EVENTS_SENDER_THREAD_H__
#define __EVENTS_SENDER_THREAD_H__

// Commons Libraries
#include <Thread.h>
#include <shaque.h>
#include <Socket.h>
#include <events/GameStatusEvent.h>
#include <events/ClientEvent.h>

// Client Libraries
#include "../BlockingQueue.hpp"

using namespace std;

class EventsSenderThread : public Thread {
private:
    Socket &socket;
    BlockingQueue<ClientEvent> &output_messages;

    void run() override;

    void terminate() override;

public:
    EventsSenderThread(Socket& socket, BlockingQueue<ClientEvent> &output_messages);
};


#endif //__EVENTS_SENDER_THREAD_H__
