#ifndef __GAME_THREAD_H__
#define __GAME_THREAD_H__

// STD Libraries
#include <list>
#include <vector>

// Commons Libraries
#include <events/ClientEvent.h>

// Game Libraries
#include "shaque.h"
#include "../model/Terrain.h"

class ClientThread;
class WalkingUnit;

class Game {
    private:
    bool is_on;
    shaque<ClientEvent>& events_queue;
    const std::vector<ClientThread*>& clients;
    std::list<ClientEvent> events;

    Terrain terrain;
    Point initial_pos = Point(30, 20);

    void sendMapConfigurationEvent();

    void collectEvents();

    void updateModel(WalkingUnit& unit);

    void updateClients(WalkingUnit& unit);

    public:
    Game(shaque<ClientEvent>& events_queue, const std::vector<ClientThread*>& _clients);

    void start();

    void stop();
};

#endif // __GAME_THREAD_H__
