#include "Game.h"

#include <iostream>

Game::Game(shaque<std::string>& _sharedQueue, unsigned int _size)
: sharedQueue(_sharedQueue) {
    size = _size;
}

void Game::run() {
    while (this->isRunning()) {
        collectEvents();
        updateModel();
        updateClients();
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

void Game::collectEvents() {
    events = sharedQueue.popAll();
}

void Game::updateModel() {
    for (std::string event : events) {
        std::cout << event << std::endl;
    }
}

void Game::updateClients() {
    for (const Client* client : clients) {
        client->send("OK");
    }
}

void Game::clientJoin(const Client* client) {
    if (clients.size() == size) return;
    clients.push_back(client);
}

bool Game::isReady() {
    return size == clients.size();
}
