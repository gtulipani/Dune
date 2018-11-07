#include "GameThread.h"

// STL Libraries
#include <iostream>

// Commons Libraries
#include <json/json.hpp>
#include <events/MapConfigurationEvent.h>
#include <events/GameStatusEvent.h>
#include <Picturable.h>

// Server Libraries
#include "ClientThread.h"
#include "../model/WalkingUnit.h"

using json = nlohmann::json;

GameThread::GameThread(shaque<ClientEvent> &events_queue, unsigned int _size)
        : events_queue(events_queue), terrain(Matrix("resources/maps/base.map")) {
    size = _size;
}

void GameThread::sendMapConfigurationEvent() {
    clients.back()->send(NotificationEvent(MAP_CONFIGURATION_EVENT));
    clients.back()->send(MapConfigurationEvent(terrain.getMatrix()));
}

void GameThread::run() {
    std::cout << "Running..." << std::endl;

    sendMapConfigurationEvent();

    // This block will be deleted in the future. The Server should probably transform Buildings, Units and the rest of
    // the model to Picturables and then send the delta
    Point picturable_origin(0, 0);
    //ID, Type, Selected, Position, Life, Motion
    std::vector<Picturable> picturables;
    picturables.emplace_back(0, "LIGHT_INFANTRY", false, picturable_origin, 100, 0);
    clients.back()->send(NotificationEvent(GAME_STATUS_EVENT));
    clients.back()->send(GameStatusEvent(picturables));

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
    for_each(events.begin(), events.end(), [&](ClientEvent event) {
        //Do stuff
    });
    // Only in case of movement?
    //unit.tick();
}

void GameThread::updateClients(WalkingUnit& unit) {
    /*Point currentStep = unit.getPixelPosition();
    ClientEvent event(1, MOVEMENT_EVENT, currentStep);
    clients.back()->send(event);*/
}

void GameThread::clientJoin(const ClientThread *client) {
    if (clients.size() != size) {
        clients.push_back(client);
    }
}

bool GameThread::isReady() {
    return size == clients.size();
}
