#ifndef __ACCEPTER_H__
#define __ACCEPTER_H__

#include <string>
#include <vector>
#include "shaque"
#include "Socket.h"
#include "Thread.h"
#include "Client.h"

class Accepter : public Thread {
    private:
    Socket socket;
    std::vector<Client*> clients;
    shaque<std::string>& sharedQueue;

    void removeFinishedClients();

    void deleteClients();

    virtual void run() override;

    virtual void terminate() override;

    public:
    explicit Accepter(std::string port, shaque<std::string>& sharedQueue);
};

#endif // __ACCEPTER_H__
