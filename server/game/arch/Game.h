#ifndef __GAME_H__
#define __GAME_H__

// STD Libraries
#include <list>
#include <vector>

// Commons Libraries
#include <Thread.h>
#include <Map.h>
#include <WalkingUnit.h>

// Game Libraries
#include "Client.h"
#include "shaque.h"


class Game : public Thread {
    private:
    unsigned int size;
    shaque<std::string> events_queue;

    std::vector<const Client*> clients;
    std::list<std::string> events;
    Map map = Map("maps/basic_map.map");
    Point initial_pos = Point(0, 0);
    WalkingUnit unit = WalkingUnit(map, initial_pos, 100);

    virtual void run() override;

    void collectEvents();

    void updateModel();

    void updateClients();

    void tick();

    public:
    Game(shaque<std::string>& events_queue, unsigned int _size);

    void clientJoin(const Client* client);

    bool isReady();
};

#endif
