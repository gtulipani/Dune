#ifndef __GAME_THREAD_H__
#define __GAME_THREAD_H__

// STD Libraries
#include <list>
#include <vector>

// Commons Libraries
#include <Thread.h>
#include <Event.h>
#include <Terrain.h>

// Game Libraries
#include "shaque.h"

class ClientThread;
class Unit;

class GameThread : public Thread {
private:
    unsigned int size;
    shaque<Event> events_queue;

    std::vector<const ClientThread*> clients;
    std::list<Event> events;
    Terrain terrain;
    Point initial_pos = Point(0, 0);

    void sendMapConfigurationEvent();

    virtual void run() override;

    void collectEvents();

    void updateModel(Unit& unit);

    void updateClients();

    public:
    GameThread(shaque<Event>& events_queue, unsigned int _size);

    void clientJoin(const ClientThread* client);

    bool isReady();
};

#endif // __GAME_THREAD_H__
