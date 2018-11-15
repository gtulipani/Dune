#include "Game.h"

// STL Libraries
#include <iostream>
#include <stdexcept>

// Commons Libraries
#include <json/json.hpp>
#include <events/MapConfigurationEvent.h>
#include <events/GameStatusEvent.h>
#include <Picturable.h>
#include <PicturableType.h>

// Server Libraries
#include "ClientThread.h"
#include "../model/WalkingUnit.h"

using json = nlohmann::json;

Game::Game(shaque<ClientEvent>& events_queue, const std::vector<ClientThread*>& _clients) :
events_queue(events_queue), clients(_clients),
map(Matrix("resources/maps/basic_map.map")), eventsHandler(gameObjects, map) {}

void Game::sendMapConfigurationEvent() {
    clients.back()->send(NotificationEvent(MAP_CONFIGURATION_EVENT));
    clients.back()->send(MapConfigurationEvent(map.getMatrix()));
}

void Game::start() {
    is_on = true;
    std::cout << "Running..." << std::endl;

    sendMapConfigurationEvent();

    //test_events();

    while (is_on) {
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
    for (ClientEvent event : events) {
        if (event.type == LEFT_CLICK_TYPE) {
            eventsHandler.leftClick(event.position);
        } else if (event.type == RIGHT_CLICK_TYPE) {
            eventsHandler.rightClick(event.position);
        } else if (event.type == CREATE_WALKING_UNIT_TYPE) {
            eventsHandler.createWalkingUnit(event.position);
        }
    }
}

void Game::tick() {
    for (GameObject* gameObject : gameObjects) {
        // We let know all the objects that time has passed
        gameObject->tick();
    }
}

void Game::updateClients() {
    // get all the objects whos status has changed
    std::vector<Picturable> states;
    for (GameObject* gameObject : gameObjects) {
        if (gameObject->haveYouChanged()) {
            states.push_back(gameObject->getState());
        }
    }

    if (!states.empty()) {
        // send the status of all objects that changed
        for (ClientThread* client : clients) {
            client->send(NotificationEvent(GAME_STATUS_EVENT));
            client->send(GameStatusEvent(states));
        }
    }
}

void Game::stop() {
    is_on = false;
}

void Game::test_events() {
    
}

Game::~Game() {
    for (GameObject* gameObject : gameObjects) {
        delete gameObject;
    }
}
