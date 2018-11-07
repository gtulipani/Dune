#include "GameThread.h"

// STL Libraries
#include <iostream>

// Commons Libraries
#include <json.hpp>
#include <MapConfigurationEvent.h>
#include <Tick.h>

// Server Libraries
#include "ClientThread.h"
#include "../model/WalkingUnit.h"

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

    Point destiny(0, 52);
    Event event(1, MOVEMENT_EVENT, destiny);
    events_queue.push(event);
    WalkingUnit test_unit(terrain, initial_pos, 10);

    while (this->isRunning()) {
        collectEvents();
        updateModel(test_unit);
        updateClients(test_unit);
        std::this_thread::sleep_for(std::chrono::milliseconds(TICK_RATE_MILLISECONDS));
    }
}

void GameThread::collectEvents() {
    events = events_queue.popAll();
}

void GameThread::updateModel(WalkingUnit &unit) {
    for_each(events.begin(), events.end(), [&](Event event) {
       if (event.type == MOVEMENT_EVENT) {
           Point destiny = event.getDestiny();
           unit.goTo(destiny);
       }
    });
    unit.tick();
}

void GameThread::updateClients(WalkingUnit& unit) {
    Point currentStep = unit.getPixelPosition();
    Event event(1, MOVEMENT_EVENT, currentStep);
    clients.back()->send(event);
}

void GameThread::clientJoin(const ClientThread *client) {
    if (clients.size() != size) {
        clients.push_back(client);
    }
}

bool GameThread::isReady() {
    return size == clients.size();
}
