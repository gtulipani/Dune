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
#include <UnitsAndBuildings.h>

// Server Libraries
#include "../json/JSONConversion.h"
#include "ClientThread.h"
#include "../model/WalkingUnit.h"

using json = nlohmann::json;

Game::Game(shaque<ClientEvent>& events_queue, const std::vector<ClientThread*>& _clients,
const GameConfiguration& gameConfig) :
events_queue(events_queue), clients(_clients) {
    map = json_utils::parseAsJson("resources/maps/basic_map.json");
    gameControler = new GameControler(map, gameConfig);
}

void Game::sendGameConfigurationEvent() {
    int player_id = 0;
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
        switch (event.type) {
            case LEFT_CLICK_EVENT_TYPE: {
                gameControler->leftClick(event.player_id, event.release_position);
                break;
            }
            case RIGHT_CLICK_EVENT_TYPE: {
                gameControler->rightClick(event.player_id, event.release_position);
                break;
            }
            case CREATE_TRIKE_TYPE: {
                gameControler->createVehiculo(event.player_id, TRIKE);
                break;
            }
            case CREATE_LIGHT_FACTORY_TYPE: {
                gameControler->createBuilding(event.player_id, LIGHT_FACTORY);
                break;
            }
            case CREATE_WIND_TRAPS_TYPE: {
                gameControler->createBuilding(event.player_id, WIND_TRAPS);
                break;
            }
            case LOCATE_BUILDING_TYPE: {
                gameControler->locateBuildingAt(event.player_id, event.picturable_id, event.release_position);
            }
            default:
                break;
        }
    }
}

void Game::updateClients() {
    std::vector<Picturable> state;
    GameStatusEvent statusEvent;
    for (unsigned int i = 0; i < clients.size(); i++) {
        statusEvent = gameControler->getStateFor(i);
        try {
            clients.at(i)->send(NotificationEvent(GAME_STATUS_EVENT));
            clients.at(i)->send(statusEvent);
        } catch (const SOException& e) {}
    }
}

void Game::stop() {
    is_on = false;
}

Game::~Game() {
    delete gameControler;
}
