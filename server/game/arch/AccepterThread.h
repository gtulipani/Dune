#ifndef __ACCEPTER_H__
#define __ACCEPTER_H__

// STL Libraries
#include <string>
#include <vector>

// Commons Libraries
#include "Socket.h"

// Server Libraries
#include "GameThread.h"

class NotificationEvent;

class AccepterThread : public Thread {
    private:
    Socket socket;
    shaque<ClientEvent> sharedQueue;
    GameThread game;
    std::vector<ClientThread*> clients;

    std::mutex m;

    NotificationEvent buildConnectionSuccessEvent();

    void notifyGameStart();

    void removeFinishedClients();

    void deleteClients();

    virtual void run() override;

    virtual void terminate() override;

    public:
    explicit AccepterThread(std::string port, unsigned int gameSize);
};

#endif // __ACCEPTER_H__
