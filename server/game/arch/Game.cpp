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
    events_queue(events_queue),
    clients(_clients),
    terrain(Matrix("resources/maps/base.map")) {
        selectedObject = nullptr;
    }

void Game::sendMapConfigurationEvent() {
    clients.back()->send(NotificationEvent(MAP_CONFIGURATION_EVENT));
    clients.back()->send(MapConfigurationEvent(terrain.getMatrix()));
}

void Game::start() {
    is_on = true;
    std::cout << "Running..." << std::endl;

    sendMapConfigurationEvent();

    //test_events();

    while (is_on) {
        collectEvents();
        updateModel();
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
            if (selectedObject != nullptr) {
                selectedObject->unselect();
                selectedObject = nullptr;
            } 
            for (GameObject* gameObject : gameObjects) {
                bool success = gameObject->tryToSelect(event.position);
                if (success) {
                    selectedObject = gameObject;
                    std::cout << "Unit selected!" <<std::endl;
                    break;
                }
            }
        } else if (event.type == RIGHT_CLICK_TYPE) {
            if (selectedObject != nullptr) {
                selectedObject->handleRightClick(event.position);
            }
        } else if (event.type == CREATE_WALKING_UNIT_TYPE) {
            auto * unit = new WalkingUnit(0, 0, {32, 32}, terrain, event.position, 10);
            gameObjects.push_back(unit);
        }
    }

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
    // In this space you can push some events to test functionality.
    // In the future, these events will be pushed by Clients
    Point initial_pos(30, 21);
    ClientEvent event0(0, CREATE_WALKING_UNIT_TYPE, initial_pos);
    events_queue.push(event0);
    ClientEvent event1(0, LEFT_CLICK_TYPE, initial_pos);
    events_queue.push(event1);
    Point dest(0, 52);
    ClientEvent event2(1, RIGHT_CLICK_TYPE, dest);
    events_queue.push(event2);
}

Game::~Game() {
    for (GameObject* gameObject : gameObjects) {
        delete gameObject;
    }
}
