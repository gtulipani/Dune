#ifndef __ACCEPTER_H__
#define __ACCEPTER_H__

// STL Libraries
#include <string>
#include <vector>

// Commons Libraries
#include <Socket.h>

// Server Libraries
#include "Game.h"
#include "shaque.h"

struct NotificationEvent;

class Accepter {
    private:
    bool is_on;
    bool _wasInterrupted;
    unsigned int clientsToAccept;
    Socket socket;
    std::vector<ClientThread*>& clients;

    NotificationEvent buildConnectionSuccessEvent();

    void notifyGameStart();

    void removeFinishedClients();

    void deleteClients();

    public:
    explicit Accepter(std::string port, unsigned int _clientsToAccept,
                      std::vector<ClientThread*>& clientVec);

    void start(shaque<ClientEvent>& sharedQueue);

    bool wasInterrupted() const;

    void stop();
};

#endif // __ACCEPTER_H__
