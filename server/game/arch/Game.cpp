#include "Game.h"

// STL Libraries
#include <iostream>
#include <stdexcept>

// Commons Libraries
#include <json/json.hpp>
#include <json/JSONUtils.h>
#include <events/MapConfigurationEvent.h>
#include <events/GameStatusEvent.h>
#include <Picturable.h>
#include <PicturableType.h>

// Server Libraries
#include "../json/JSONConversion.h"
#include "ClientThread.h"
#include "../model/WalkingUnit.h"

using json = nlohmann::json;

Game::Game(shaque<ClientEvent>& events_queue, const std::vector<ClientThread*>& _clients) :
events_queue(events_queue), clients(_clients), gameControler(map) {
    map = json_utils::parseAsJson("resources/maps/basic_map.json");
}

void Game::sendMapConfigurationEvent() {
    for (ClientThread* client : clients) {
        client->send(NotificationEvent(MAP_CONFIGURATION_EVENT));
        client->send(MapConfigurationEvent(map.getMatrix()));
    }
}

void Game::sendIDsEvent() {
    unsigned int i = 0;
    for (ClientThread* client : clients) {
        ClientEvent event;
        event.player_id = i;
        i++;
        client->send(event);
    }
}

void Game::start() {
    is_on = true;
    std::cout << "Running..." << std::endl;

    sendMapConfigurationEvent();
    //sendIDsEvent();

    gameControler.initialize(clients.size());
    updateClients();

    //test_events();

    while (is_on) {
        collectEvents();
        updateModel();
        gameControler.tick();
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
            gameControler.leftClick(event.player_id, event.position);
        } else if (event.type == RIGHT_CLICK_TYPE) {
            gameControler.rightClick(event.player_id, event.position);
        } else if (event.type == CREATE_WALKING_UNIT_TYPE) {
            gameControler.createWalkingUnit(event.player_id, event.position);
        } else if (event.type == CREATE_COSECHADORA_TYPE) {
            gameControler.createCosechadora(event.player_id, event.position);
        } else if (event.type == CREATE_BUILDING_TYPE) {
            gameControler.createBuilding(event.player_id);
        } else if (event.type == LOCATE_BUILDING_TYPE) {
            gameControler.putBuildingAt(event.player_id, event.position);
        }
    }
}

void Game::updateClients() {
    // get all the objects whos status has changed
    std::vector<Picturable> states = gameControler.getStates();

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
