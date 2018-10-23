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
    bool is_on;

    void removeFinishedClients();

    void deleteClients();

    public:
    explicit Accepter(std::string port, shaque<std::string>& sharedQueue);

    virtual void run() override;

    virtual void stop() override;

    virtual bool hasFinished() const override;

    ~Accepter();
};

#endif // __ACCEPTER_H__
