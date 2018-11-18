#ifndef __GAME_THREAD_H__
#define __GAME_THREAD_H__

// Commons Libraries
#include <Socket.h>
#include <Thread.h>
#include <shaque.h>
#include <events/ClientEvent.h>
#include <events/NotificationEvent.h>
#include <events/GameStatusEvent.h>

// Client libraries
#include "WindowController.h"
#include "BlockingQueue.hpp"

union SDL_Event;

class EventsLooperThread : public Thread {
private:
    shaque<GameStatusEvent> &game_status_events;
    BlockingQueue<ClientEvent> &output_messages;
    WindowController window_controller;

    // This property should not be used. It's moved to the WindowController
    Matrix terrain_matrix;

    void pushEvent(std::string message, Point position);
    void processServerEvents();

    void processMouseEvent(SDL_Event& event);
    void processKeyDownEvent(SDL_Event& event);

    void run() override;
public:
    EventsLooperThread(shaque<GameStatusEvent> &game_status_events, BlockingQueue<ClientEvent> &output_messages);

    void configure(Matrix matrix);
};


#endif //__GAME_THREAD_H__
