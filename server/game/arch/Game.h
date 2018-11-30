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
#include "GameConfiguration.h"
#include "../model/Map.h"

class ClientThread;
class GameObject;
class Player;

class Game {
    private:
    bool is_on;
    shaque<ClientEvent>& events_queue;
    const std::vector<ClientThread*>& vec_clients;
    std::map<int, ClientThread*> clients;
    std::list<ClientEvent> events;

    Map map;
    GameControler* gameControler;

    void sendGameConfigurationEvent();

    void collectEvents();

    void updateModel();

    void updateClients();

    public:
    Game(shaque<ClientEvent>& events_queue, const std::vector<ClientThread*>& _clients, const GameConfiguration& gameConfig);

    void start();

    void stop();

    ~Game();
};

#endif // __GAME_H__
