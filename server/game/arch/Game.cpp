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
    terrain(Matrix("resources/maps/base.map")) {}

void Game::sendMapConfigurationEvent() {
    clients.back()->send(NotificationEvent(MAP_CONFIGURATION_EVENT));
    clients.back()->send(MapConfigurationEvent(terrain.getMatrix()));
}

void Game::start() {
    is_on = true;
    std::cout << "Running..." << std::endl;

    sendMapConfigurationEvent();

    // This block will be deleted in the future. The Server should probably transform Buildings, Units and the rest of
    // the model to Picturables and then send the delta
    Point picturable_origin(0, 0);
    //ID, Type, Selected, Position, Life, Motion
    std::vector<Picturable> picturables;
    picturables.emplace_back(0, LIGHT_INFANTRY, 0, false, picturable_origin, 100);
    clients.back()->send(NotificationEvent(GAME_STATUS_EVENT));
    clients.back()->send(GameStatusEvent(picturables));

    // Manualy pushes two events.
    Point initial_pos(30, 21);
    ClientEvent event1(0, LEFT_CLICK_TYPE, initial_pos);
    events_queue.push(event1);
    Point dest(0, 52);
    ClientEvent event2(1, RIGHT_CLICK_TYPE, dest);
    events_queue.push(event2);

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
            GameObject* gameObject;
            try {
                gameObject = positions.at(event.position);
                gameObject->select();
            } catch (const out_of_range& e) {
                selectedObject->unselect();
                selectedObject = nullptr;
            }
        } else if (event.type == RIGHT_CLICK_TYPE) {
            if (selectedObject != nullptr) {
                selectedObject->handleRightClick(event.position);
            }
        } else if (event.type == CREATE_WALKING_UNIT_TYPE) {
            auto * unit = new WalkingUnit(0, 0, terrain, event.position, 10);
            gameObjects.push_back(unit);
            positions[event.position] = unit;
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

    // send the status of all objects that changed
    for (ClientThread* client : clients) {
        client->send(NotificationEvent(GAME_STATUS_EVENT));
        client->send(GameStatusEvent(states));
    }
}

void Game::stop() {
    is_on = false;
}
