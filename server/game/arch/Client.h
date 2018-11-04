#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <Event.h>
#include "shaque.h"
#include "../../commons/Thread.h"
#include "../../commons/Socket.h"

class Client : public Thread {
    private:
    Socket socket;
    shaque<Event>& sharedQueue;

    void handleMsgError();

    void handleMsgSuccess(const std::string& msg);

    virtual void run() override;

    virtual void terminate() override;

    public:
    Client(Socket _socket, shaque<Event>& _sharedQueue);

    void send(const std::string& msg) const;
};

#endif // __CLIENT_H__
