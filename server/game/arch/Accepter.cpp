#include "Accepter.h"

#include "SOException.h"

#define MAX_CLIENTS_IN_WAIT 20

Accepter::Accepter(std::string port, unsigned int gameSize) :
socket(nullptr, port.c_str()), game(sharedQueue, gameSize),
sharedQueue(m) {
    socket.bindAndListen(MAX_CLIENTS_IN_WAIT);
}

void Accepter::run() {
    while (this->isRunning()) {
        try {
            Socket peer = socket.acceptClient();
            clients.push_back(new Client(std::move(peer), sharedQueue));
            game.clientJoin(clients.back());
            clients.back()->start();
            removeFinishedClients();
            if (game.isReady()) {
                this->stop();
                game.start();
                game.join();
            }
        } catch (const SOException& e) {
            this->stop();
        }
    }
    deleteClients();
}

void Accepter::removeFinishedClients() {
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

void Accepter::deleteClients() {
    int n = clients.size();
    for (int i = 0; i < n; i++) {
        clients.at(i)->stop();
        clients.at(i)->join();
    }
    clients.clear();
}

void Accepter::terminate() {
    socket.shutDown();
    if (game.isRunning()) {
        game.stop();
        game.join();
    }
}