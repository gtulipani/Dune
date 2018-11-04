#ifndef __ACCEPTER_H__
#define __ACCEPTER_H__

#include <string>
#include <vector>
#include "shaque.h"
#include "../../commons/Socket.h"
#include "../../commons/Thread.h"
#include "Client.h"
#include "Game.h"

class Accepter : public Thread {
    private:
    Socket socket;
    shaque<Event> sharedQueue;
    Game game;
    std::vector<Client*> clients;

    std::mutex m;

    void removeFinishedClients();

    void deleteClients();

    virtual void run() override;

    virtual void terminate() override;

    public:
    explicit Accepter(std::string port, unsigned int gameSize);
};

#endif // __ACCEPTER_H__
