#ifndef __CLIENT_THREAD_H__
#define __CLIENT_THREAD_H__

#include <Event.h>
#include "shaque.h"
#include "../../commons/Thread.h"
#include "../../commons/Socket.h"

class ClientThread : public Thread {
    private:
    Socket socket;
    shaque<Event>& sharedQueue;

    void handleMsgError();

    virtual void run() override;

    virtual void terminate() override;

    public:
    ClientThread(Socket _socket, shaque<Event>& _sharedQueue);

    void send(const std::string& msg) const;

    void send(const Event& event) const;
};

#endif // __CLIENT_THREAD_H__
