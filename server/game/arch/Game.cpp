#include "Game.h"
#include <iostream>
#include <json.hpp>

using json = nlohmann::json;

Game::Game(shaque<Event> &events_queue, unsigned int _size)
        : events_queue(events_queue) {
    size = _size;
}

void Game::run() {
    std::cout << "Running..." << std::endl;
    Point source = unit.stepAndGetPixelPosition();
    Point destiny(0, 1);
    Event event("MOVEMENT", source, destiny);
    events_queue.push(event);

    //sharedQueue.push("0,1");
    while (this->isRunning()) {
        collectEvents();
        updateModel();
        updateClients();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void Game::collectEvents() {
    events = events_queue.popAll();
}

void Game::updateModel() {
    if (!events.empty()) {
        Event event = events.front();
        Point destiny = event.getDestiny();
        unit.goTo(destiny);
        json event_json = event;
        std::string msg = event_json.dump();
        clients.back()->send(msg);
        Point new_destiny = Point(destiny.row, destiny.col + 1);
        Event new_event = Event("MOVEMENT", destiny, new_destiny);
        events_queue.push(new_event);
    }
}

void Game::updateClients() {
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
