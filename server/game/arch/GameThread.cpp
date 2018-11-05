#include "GameThread.h"

// STL Libraries
#include <iostream>

// Commons Libraries
#include <json.hpp>
#include <Unit.h>
#include <MapConfigurationEvent.h>

// Server Libraries
#include "ClientThread.h"

using json = nlohmann::json;

GameThread::GameThread(shaque<Event> &events_queue, unsigned int _size)
        : events_queue(events_queue), terrain(Matrix("resources/maps/base.map")) {
    size = _size;
}

void GameThread::sendMapConfigurationEvent() {
    clients.back()->send(MapConfigurationEvent(terrain.getMatrix()));
}

void GameThread::run() {
    std::cout << "Running..." << std::endl;

    sendMapConfigurationEvent();

    Point destiny(0, 1);
    Event event(1, MOVEMENT_EVENT, destiny);
    events_queue.push(event);
    Unit test_unit(terrain, initial_pos);

    while (this->isRunning()) {
        collectEvents();
        updateModel(test_unit);
        updateClients();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void GameThread::collectEvents() {
    events = events_queue.popAll();
}

void GameThread::updateModel(Unit &unit) {
    for_each(events.begin(), events.end(), [&](Event event) {
       if (event.type == MOVEMENT_EVENT) {
           Point destiny = event.getDestiny();
           unit.goTo(destiny);
           Point new_destiny = Point(destiny.row, destiny.col + 1);
           Event new_event = Event(1, MOVEMENT_EVENT, new_destiny);
           events_queue.push(new_event);
       }
       clients.back()->send(event);
    });
}

void GameThread::updateClients() {
}

void GameThread::clientJoin(const ClientThread *client) {
    if (clients.size() != size) {
        clients.push_back(client);
    }
}

bool GameThread::isReady() {
    return size == clients.size();
}
