#ifndef __GAME_H__
#define __GAME_H__

#include <list>
#include <vector>
#include "Client.h"
#include "shaque.h"
#include "../../commons/Thread.h"

class Game : public Thread {
    private:
    unsigned int size;
    std::vector<const Client*> clients;
    std::list<std::string> events;
    shaque<std::string>& sharedQueue;

    virtual void run() override;

    void collectEvents();

    void updateModel();

    void updateClients();

    public:
    Game(shaque<std::string>& _sharedQueue, unsigned int _size);

    void clientJoin(const Client* client);

    bool isReady();
};

#endif
