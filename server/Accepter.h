#ifndef __ACCEPTER_H__
#define __ACCEPTER_H__

#include <string>
#include <vector>
#include "Socket.h"
#include "Thread.h"
#include "Client.h"

class Accepter : public Thread {
    private:
    Socket socket;
    std::vector<Client*> clients;
    bool is_on;

    void removeFinishedClients();

    void deleteClients();

    public:
    explicit Accepter(std::string port);

    virtual void run() override;

    void stop();

    ~Accepter();
};

#endif
