#include "AccepterThread.h"

// Commons Libraries
#include <events/NotificationEvent.h>

// Server Libraries
#include "SOException.h"
#include "ClientThread.h"

#define MAX_CLIENTS_IN_WAIT 20

AccepterThread::AccepterThread(std::string port, unsigned int gameSize) :
    socket("", port),
    sharedQueue(m),
    game(sharedQueue, gameSize) {
        socket.bindAndListen(MAX_CLIENTS_IN_WAIT);
}

NotificationEvent AccepterThread::buildConnectionSuccessEvent() {
    return NotificationEvent(CONNECTION_SUCCESS_EVENT);
}

void AccepterThread::notifyGameStart() {
    NotificationEvent event(GAME_STARTED_EVENT);
    std::for_each(clients.begin(), clients.end(), [event](ClientThread* client) {
        client->send(event);
    });
}

void AccepterThread::run() {
    while (this->isRunning()) {
        try {
            Socket peer = socket.acceptClient();
            clients.push_back(new ClientThread(std::move(peer), sharedQueue));
            game.clientJoin(clients.back());
            clients.back()->start();
            clients.back()->send(buildConnectionSuccessEvent());
            removeFinishedClients();
            if (game.isReady()) {
                this->stop();
                notifyGameStart();
                game.start();
                game.join();
            }
        } catch (const SOException& e) {
            this->stop();
        }
    }
    deleteClients();
}

void AccepterThread::removeFinishedClients() {
    unsigned int i = 0;
    while (i < clients.size()) {
        if (!clients.at(i)->isRunning()) {
            clients.at(i)->join();
            clients.erase(clients.begin() + i);
        } else {
            i++;
        }
    }
}

void AccepterThread::deleteClients() {
    int n = clients.size();
    for (int i = 0; i < n; i++) {
        clients.at(i)->stop();
        clients.at(i)->join();
    }
    clients.clear();
}

void AccepterThread::terminate() {
    socket.shutDown();
    if (game.isRunning()) {
        game.stop();
        game.join();
    }
}

