#ifndef __CLIENT_H__
#define __CLIENT_H__

// Commons Libraries
#include <shaque.h>
#include <events/ClientEvent.h>
#include <events/GameStatusEvent.h>
#include <events/GameConfigurationEvent.h>

// Client Libraries
#include "threads/EventsLooperThread.h"
#include "threads/EventsReceptorThread.h"
#include "threads/EventsSenderThread.h"

class Client {
private:
    string host;
    string port;
    bool game_ended;
    std::mutex game_status_mutex;
    std::mutex output_messages_mutex;
    shaque<GameStatusEvent> game_status_events;
    BlockingQueue<ClientEvent> output_messages;
    EventsLooperThread events_looper_thread;
    EventsReceptorThread events_receptor_thread;
    EventsSenderThread events_sender_thread;

    Socket socket;

    void waitForEvent(int message);
    GameConfigurationEvent receiveGameConfiguration();

public:
    Client(string host, string port);

    void start();
};


#endif //__CLIENT_H__
