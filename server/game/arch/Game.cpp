#include "Game.h"

#include <iostream>

Game::Game(shaque<std::string>& _sharedQueue, unsigned int _size)
: sharedQueue(_sharedQueue) {
    size = _size;
}

void Game::run() {
    std::cout << "Running..." << std::endl;
    while (this->isRunning()) {
        collectEvents();
        updateModel();
        getState();
        updateClients();
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

void Game::collectEvents() {
    events = sharedQueue.popAll();
}

void Game::updateModel() {
    if (!events.empty()) {
        std::string strPos = events.front();
        int i = strPos.find(',');
        int row = std::stoi(strPos.substr(0, i));
        int col = std::stoi(strPos.substr(i + 2));
        Point goal = Point(row, col);
        unit.goTo(goal);
    }
}

void Game::getState() {
    Point pos = unit.stepAndGetPixelPosition();
    std::string msg = pos.row + ", " + pos.col;
    clients.back()->send(msg);
}

void Game::updateClients() {

}

void Game::clientJoin(const Client* client) {
    if (clients.size() == size) return;
    clients.push_back(client);
}

bool Game::isReady() {
    return size == clients.size();
}
