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
    unsigned int player_id{};
    shaque<GameStatusEvent> &game_status_events;
    BlockingQueue<ClientEvent> &output_messages;
    WindowController window_controller;
    bool &game_ended;

    void pushEvent(int client_event_type, std::vector<int> picturable_ids, Point click_position, Point release_position);
    void processServerEvents();

    void processMouseClickEvent(SDL_Event &event);
    void processMouseReleaseEvent(SDL_Event &event);

    void processKeyDownEvent(SDL_Event& event);

    void run() override;
public:
    EventsLooperThread(shaque<GameStatusEvent> &game_status_events, BlockingQueue<ClientEvent> &output_messages, bool &game_ended);

    void configure(unsigned int player_id, Matrix matrix);
};


#endif //__GAME_THREAD_H__
