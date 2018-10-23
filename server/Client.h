#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "shaque"
#include "Thread.h"
#include "Socket.h"

class Client : public Thread {
    private:
    Socket socket;
    shaque<std::string> sharedQueue;
    bool is_on;

    void handleMsgError();

    void handleMsgSuccess(std::string msg);

    public:
    Client(Socket _socket, shaque<std::string> _sharedQueue);

    virtual void run() override;

    virtual void stop() override;

    virtual bool hasFinished() const override;
};

#endif // __CLIENT_H__
