#include "Game.h"

// STL Libraries
#include <iostream>
#include <stdexcept>

// Commons Libraries
#include <json/json.hpp>
#include <json/JSONUtils.h>
#include <events/GameConfigurationEvent.h>
#include <events/GameStatusEvent.h>
#include <Picturable.h>

// Server Libraries
#include "../json/JSONConversion.h"
#include "ClientThread.h"
#include "../model/WalkingUnit.h"

using json = nlohmann::json;

Game::Game(shaque<ClientEvent>& events_queue, const std::vector<ClientThread*>& _clients) :
events_queue(events_queue), clients(_clients), gameControler(map) {
    map = json_utils::parseAsJson("resources/maps/basic_map.json");
}

void Game::sendGameConfigurationEvent() {
    unsigned int player_id = 0;
    for (ClientThread* client : clients) {
        client->send(NotificationEvent(GAME_CONFIGURATION_EVENT));
        client->send(GameConfigurationEvent(player_id, map.getMatrix()));
        player_id++;
    }
}

void Game::start() {
    is_on = true;
    std::cout << "Running..." << std::endl;

    sendGameConfigurationEvent();

    gameControler.initialize(clients.size());
    updateClients();

    while (is_on) {
        collectEvents();
        updateModel();
        gameControler.tick();
        updateClients();
        gameControler.updateGameObjects();
        std::this_thread::sleep_for(std::chrono::milliseconds(TICK_RATE_MILLISECONDS));
    }
}

void Game::collectEvents() {
    events = events_queue.popAll();
}

void Game::updateModel() {
    for (ClientEvent event : events) {
        if (event.type == LEFT_CLICK_TYPE) {
            gameControler.leftClick(event.player_id, event.release_position);
        } else if (event.type == RIGHT_CLICK_TYPE) {
            gameControler.rightClick(event.player_id, event.release_position);
        } else if (event.type == CREATE_TRIKE_TYPE) {
            gameControler.createTrike(event.player_id);
        } else if (event.type == CREATE_BUILDING_LIGHT_FACTORY) {
            gameControler.createBuilding(event.player_id, LIGHT_FACTORY);
        } else if (event.type == CREATE_BUILDING_WIND_TRAPS) {
            gameControler.createBuilding(event.player_id, WIND_TRAPS);
        } else if (event.type == LOCATE_BUILDING_TYPE) {
            gameControler.locateBuildingAt(event.player_id, event.release_position);
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
