#ifndef __GAME_THREAD_H__
#define __GAME_THREAD_H__

// STD Libraries
#include <list>
#include <vector>

// Commons Libraries
#include <events/ClientEvent.h>

// Game Libraries
#include "shaque.h"

// Model Libraries
#include "../model/GameObject.h"
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
    std::unordered_map<Point, GameObject*> positions;
    std::vector<GameObject*> gameObjects;
    GameObject* selectedObject;

    void sendMapConfigurationEvent();

    void collectEvents();

    void updateModel();

    void updateClients();

    public:
    Game(shaque<ClientEvent>& events_queue, const std::vector<ClientThread*>& _clients);

    void start();

    void stop();
};

#endif // __GAME_THREAD_H__
