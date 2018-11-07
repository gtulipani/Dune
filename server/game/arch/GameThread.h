#ifndef __GAME_THREAD_H__
#define __GAME_THREAD_H__

// STD Libraries
#include <list>
#include <vector>

// Commons Libraries
#include <Thread.h>
#include <events/ClientEvent.h>

// Game Libraries
#include "shaque.h"
#include "../model/Terrain.h"

class ClientThread;
class WalkingUnit;

class GameThread : public Thread {
private:
    unsigned int size;
    shaque<ClientEvent> events_queue;

    std::vector<const ClientThread*> clients;
    std::list<ClientEvent> events;
    Terrain terrain;
    Point initial_pos = Point(30, 20);

    void sendMapConfigurationEvent();

    virtual void run() override;

    void collectEvents();

    void updateModel(WalkingUnit& unit);

    void updateClients(WalkingUnit& unit);

    public:
    GameThread(shaque<ClientEvent>& events_queue, unsigned int _size);

    void clientJoin(const ClientThread* client);

    bool isReady();
};

#endif // __GAME_THREAD_H__
