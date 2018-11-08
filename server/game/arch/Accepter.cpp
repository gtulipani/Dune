#include "Accepter.h"

// Commons Libraries
#include <events/NotificationEvent.h>

// Server Libraries
#include "SOException.h"
#include "ClientThread.h"

Accepter::Accepter(std::string port, unsigned int _clientsToAccept,
std::vector<ClientThread*>& _clientsVec) : socket("", port),
clients(_clientsVec) {
        socket.bindAndListen(_clientsToAccept);
        clientsToAccept = _clientsToAccept;
}

NotificationEvent Accepter::buildConnectionSuccessEvent() {
    return NotificationEvent(CONNECTION_SUCCESS_EVENT);
}

void Accepter::notifyGameStart() {
    NotificationEvent event(GAME_STARTED_EVENT);
    std::for_each(clients.begin(), clients.end(), [event](ClientThread* client) {
        client->send(event);
    });
}

void Accepter::start(shaque<ClientEvent>& sharedQueue) {
    is_on = true;
    unsigned int i = 0;
    while (is_on && i < clientsToAccept) {
        try {
            Socket peer = socket.acceptClient();
            if (peer.valid()) {
                clients.push_back(new ClientThread(std::move(peer), sharedQueue));
                clients.back()->start();
                clients.back()->send(buildConnectionSuccessEvent());
                i++;
            }
        } catch (const SOException& e) {
            this->stop();
        }
    }
    _wasInterrupted = i < clientsToAccept;
}

bool Accepter::wasInterrupted() const {
    return _wasInterrupted;
}

void Accepter::stop() {
    socket.shutDown();
    is_on = false;
}

