#include "Game.h"
#include <iostream>
#include <json.hpp>

using json = nlohmann::json;

#include "Tick.h"

Game::Game(shaque<std::string> &events_queue, unsigned int _size)
        : events_queue(events_queue) {
    size = _size;
}

void Game::run() {
    while (this->isRunning()) {
        collectEvents();
        updateModel();
        tick();
        updateClients();
        std::this_thread::sleep_for(std::chrono::milliseconds(TICK_RATE_MILLISECONDS));
    }
}

void Game::collectEvents() {
    events = events_queue.popAll();
}

void Game::updateModel() {
    // Si hay un evento, quiere decir que el cliente hizo click para mover la
    // unidad. Entonces se envio el punto, que parsea.
    // Luego actualiza el modelo para decirle a la unidad que actualice su path.
    // (goTo())
    if (!events.empty()) {
        std::string strPoint = events.back();
        int i = strPoint.find(',');
        int row = std::stoi(strPoint.substr(0, i));
        int col = std::stoi(strPoint.substr(i + 2));
        Point goal = Point(row, col);
        unit.goTo(goal);
    }
}

void Game::tick() {
    // Le avisa a la unidad que paso un tick, para que realice sus acciones
    // correspondientes.
    unit.tick();
}

void Game::updateClients() {
    // Obtiene el estado de la unidad y se lo manda al cliente
    Point p = unit.getPixelPosition();
    clients.back()->send(p.row + ", " + p.col);
}

void Game::clientJoin(const Client *client) {
    if (clients.size() != size) {
        clients.push_back(client);
    }
}

bool Game::isReady() {
    return size == clients.size();
}

void to_json(json &j, const Point &p) {
    j = json{
            {"row",    p.row},
            {"column", p.col}
    };
}

void from_json(const json &j, Point &p) {
    j.at("row").get_to(p.row);
    j.at("column").get_to(p.col);
}

void to_json(json &j, const Event &e) {
    j = json{
            {"type", e.type},
            {"src",  e.src},
            {"dst",  e.dst}
    };
}

void from_json(const json &j, Event &e) {
    j.at("type").get_to(e.type);
    j.at("src").get_to(e.src);
    j.at("dst").get_to(e.dst);
}
