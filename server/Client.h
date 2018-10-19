#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "Thread.h"
#include "Socket.h"

class Client : public Thread {
    private:
    Socket socket;
    bool is_on;

    public:
    Client(Socket _socket);

    virtual void run() override;

    bool hasFinished() const;

    void stop();
};

#endif
