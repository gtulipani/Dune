#include "Game.h"

// STL Libraries
#include <iostream>
#include <stdexcept>
#include <chrono>

// Commons Libraries
#include <json/json.hpp>
#include <json/JSONUtils.h>
#include <events/GameConfigurationEvent.h>
#include <events/GameStatusEvent.h>
#include <Picturable.h>
#include <SOException.h>

// Server Libraries
#include "../json/JSONConversion.h"
#include "ClientThread.h"
#include "../model/WalkingUnit.h"

using json = nlohmann::json;

Game::Game(shaque<ClientEvent>& events_queue, const std::vector<ClientThread*>& _clients) :
events_queue(events_queue), clients(_clients) {
    map = json_utils::parseAsJson("resources/maps/basic_map.json");
    gameControler = new GameControler(map);
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

    gameControler->initialize(clients.size());

    while (is_on) {
        auto start = std::chrono::steady_clock::now();
        collectEvents();
        updateModel();
        gameControler->tick();
        updateClients();
        gameControler->updateGameObjects();
        auto end = std::chrono::steady_clock::now();
        auto execution_difference = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        if (execution_difference < TICK_RATE_MILLISECONDS) {
            std::this_thread::sleep_for(TICK_RATE_MILLISECONDS - execution_difference);
        }
    }
}

void Game::collectEvents() {
    events = events_queue.popAll();
}

void Game::updateModel() {
    for (ClientEvent event : events) {
        if (event.type == LEFT_CLICK_TYPE) {
            gameControler->leftClick(event.player_id, event.release_position);
        } else if (event.type == RIGHT_CLICK_TYPE) {
            gameControler->rightClick(event.player_id, event.release_position);
        } else if (event.type == CREATE_TRIKE_TYPE) {
            gameControler->createTrike(event.player_id);
        } else if (event.type == CREATE_BUILDING_LIGHT_FACTORY) {
            gameControler->createBuilding(event.player_id, LIGHT_FACTORY);
        } else if (event.type == CREATE_BUILDING_WIND_TRAPS) {
            gameControler->createBuilding(event.player_id, WIND_TRAPS);
        } else if (event.type == LOCATE_BUILDING_TYPE) {
            gameControler->locateBuildingAt(event.player_id, event.release_position);
        }
    }
}

void Game::updateClients() {
    std::vector<Picturable> state;
    for (unsigned int i = 0; i < clients.size(); i++) {
        state = gameControler->getStateFor(i);
        if (!state.empty()) {
            try {
                clients.at(i)->send(NotificationEvent(GAME_STATUS_EVENT));
                clients.at(i)->send(GameStatusEvent(state));
            } catch (const SOException& e) {}
        }
    }
}

void Game::stop() {
    is_on = false;
}
