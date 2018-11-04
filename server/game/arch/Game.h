#ifndef __GAME_H__
#define __GAME_H__

// STD Libraries
#include <list>
#include <vector>

// Commons Libraries
#include <Thread.h>
#include <Map.h>
#include <Unit.h>
#include <Event.h>

// Game Libraries
#include "Client.h"
#include "shaque.h"


class Game : public Thread {
    private:
    unsigned int size;
    shaque<Event> events_queue;

    std::vector<const Client*> clients;
    std::list<Event> events;
    Map map = Map("maps/basic_map.map");
    Point initial_pos = Point(0, 0);
    Unit unit = Unit(map, initial_pos);

    virtual void run() override;

    void collectEvents();

    void updateModel();

    void updateClients();

    public:
    Game(shaque<Event>& events_queue, unsigned int _size);

    void clientJoin(const Client* client);

    bool isReady();
};

#endif
