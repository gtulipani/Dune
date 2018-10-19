#include "Accepter.h"

#include "SOException.h"

#define MAX_CLIENTS_IN_WAIT 20

Accepter::Accepter(std::string port) : socket(nullptr, port.c_str()) {
    socket.bindAndListen(MAX_CLIENTS_IN_WAIT);
    is_on = true;
}

void Accepter::run() {
    while (is_on) {
        try {
            Socket peer = socket.acceptClient();
            clients.push_back(new Client(std::move(peer)));
            clients.back()->start();
            //removeFinishedClients();
        } catch (const SOException& e) {
            is_on = false;
        }
    }
    deleteClients();
}

void Accepter::removeFinishedClients() {
    for (unsigned int i = 0; i < clients.size(); i++) {
        if (clients.at(i)->hasFinished()) {
            clients.at(i)->join(); // For safety
            delete clients.at(i);
            clients.erase(clients.begin() + i);
        }
    }
}

void Accepter::deleteClients() {
    int n = clients.size();
    for (int i = 0; i < n; i++) {
        clients.at(i)->stop();
        clients.at(i)->join();
        delete clients.at(i);
    }
}

void Accepter::stop() {
    is_on = false;
    socket.shutDown();
}

Accepter::~Accepter() {
    if (is_on) {
        socket.shutDown();
        is_on = false;
    }
}
