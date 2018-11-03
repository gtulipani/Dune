#ifndef __GAME_H__
#define __GAME_H__

#include <list>
#include <vector>
#include "Client.h"
#include "shaque.h"
#include "Game.h"
#include "Unit.h"
#include "Map.h"
#include "../../commons/Thread.h"

class Game : public Thread {
    private:
    unsigned int size;
    std::vector<const Client*> clients;
    std::list<std::string> events;
    shaque<std::string>& sharedQueue;
    const Map map = Map("Matrix");
    const Point initial_pos = Point(6, 3);
    Unit unit = Unit(map, initial_pos);

    virtual void run() override;

    void collectEvents();

    void updateModel();

    void getState();

    void updateClients();

    public:
    Game(shaque<std::string>& _sharedQueue, unsigned int _size);

    void clientJoin(const Client* client);

    bool isReady();
};

#endif
