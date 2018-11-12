#ifndef __CLIENT_H__
#define __CLIENT_H__

// Commons Libraries
#include <shaque.h>
#include <events/ClientEvent.h>
#include <events/GameStatusEvent.h>

// Client Libraries
#include "EventsLooperThread.h"
#include "EventsReceptorThread.h"
#include "EventsSenderThread.h"

class Client {
private:
    string host;
    string port;
    std::mutex game_status_mutex;
    std::mutex output_messages_mutex;
    shaque<GameStatusEvent> game_status_events;
    shaque<ClientEvent> output_messages;
    EventsLooperThread events_looper_thread;
    EventsReceptorThread events_receptor_thread;
    EventsSenderThread events_sender_thread;

    Socket socket;

    void waitForEvent(string message);
    Matrix receiveTerrainMatrix();

public:
    Client(string host, string port);

    void start();
};


#endif //__CLIENT_H__
