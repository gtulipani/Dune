#ifndef __GAME_H__
#define __GAME_H__

// STD Libraries
#include <vector>

// Commons Libraries
#include <events/ClientEvent.h>

// Game Libraries
#include "shaque.h"

// Model Libraries
#include "GameControler.h"
#include "../model/Map.h"

class ClientThread;
class GameObject;
class Player;

class Game {
    private:
    bool is_on;
    shaque<ClientEvent>& events_queue;
    const std::vector<ClientThread*>& clients;
    std::list<ClientEvent> events;

    Map map;
    GameControler gameControler;

    void sendGameConfigurationEvent();

    void collectEvents();

    void updateModel();

    void updateClients();

    public:
    Game(shaque<ClientEvent>& events_queue, const std::vector<ClientThread*>& _clients);

    void start();

    void stop();
};

#endif // __GAME_H__
