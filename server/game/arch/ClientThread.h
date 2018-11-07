#ifndef __CLIENT_THREAD_H__
#define __CLIENT_THREAD_H__

#include <events/ClientEvent.h>
#include <events/MapConfigurationEvent.h>
#include <events/GameStatusEvent.h>
#include <events/NotificationEvent.h>
#include "shaque.h"
#include "../../commons/Thread.h"
#include "../../commons/Socket.h"

class ClientThread : public Thread {
    private:
    Socket socket;
    shaque<ClientEvent>& sharedQueue;

    void handleMsgError();

    virtual void run() override;

    virtual void terminate() override;

    public:
    ClientThread(Socket _socket, shaque<ClientEvent>& _sharedQueue);

    void send(const std::string& msg) const;

    void send(const ClientEvent& event) const;

    void send(const MapConfigurationEvent& event) const;

    void send(const GameStatusEvent& event) const;

    void send(const NotificationEvent& event) const;
};

#endif // __CLIENT_THREAD_H__
