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

Game::Game(shaque<ClientEvent>& events_queue, const std::vector<ClientThread*>& vec_clients,
const GameConfiguration& gameConfig) :
events_queue(events_queue), vec_clients(vec_clients) {
    map = json_utils::parseAsJson("resources/maps/new_map.json");
    gameControler = new GameControler(map, gameConfig);
}

void Game::sendGameConfigurationEvent() {
    int player_id = 0;
    for (auto& client : clients) {
        client.second->send(NotificationEvent(GAME_CONFIGURATION_EVENT));
        client.second->send(GameConfigurationEvent(player_id, map.getMatrix()));
        player_id++;
    }
}

void Game::start() {

    for (unsigned int i = 0; i < vec_clients.size(); i++) {
        clients[i] = vec_clients.at(i);
    }

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
            case RIGHT_CLICK_EVENT_TYPE: {
                gameControler->rightClick(event.player_id, event.release_position);
                break;
            }
            case LEFT_CLICK_EVENT_TYPE: {
                gameControler->leftClick(event.player_id, event.click_position, event.release_position);
                break;
            }
            case CREATE_WIND_TRAPS_TYPE: {
                gameControler->createBuilding(event.player_id, WIND_TRAPS);
                break;
            }
            case CREATE_REFINERY_TYPE: {
                gameControler->createBuilding(event.player_id, REFINERY);
                break;
            }
            case CREATE_BARRACKS_TYPE: {
                gameControler->createBuilding(event.player_id, BARRACKS);
                break;
            }
            case CREATE_LIGHT_FACTORY_TYPE: {
                gameControler->createBuilding(event.player_id, LIGHT_FACTORY);
                break;
            }
            case CREATE_HEAVY_FACTORY_TYPE: {
                gameControler->createBuilding(event.player_id, HEAVY_FACTORY);
                break;
            }
            case CREATE_SILO_TYPE: {
                gameControler->createBuilding(event.player_id, SILO);
                break;
            }
            case CREATE_TRIKE_TYPE: {
                gameControler->createVehiculo(event.player_id, TRIKE);
                break;
            }
            case CREATE_HARVESTER_TYPE: {
                gameControler->createVehiculo(event.player_id, HARVESTER);
                break;
            }
            case CREATE_RAIDER_TYPE: {
                gameControler->createVehiculo(event.player_id, RAIDER);
                break;
            }
            case CREATE_TANK_TYPE: {
                gameControler->createVehiculo(event.player_id, TANK);
                break;
            }
            case CREATE_LIGHT_INFANTRY_TYPE: {
                gameControler->createInfanteria(event.player_id, LIGHT_INFANTRY);
                break;
            }
            case CREATE_HEAVY_INFANTRY_TYPE: {
                gameControler->createInfanteria(event.player_id, HEAVY_INFANTRY);
                break;
            }
            case LOCATE_BUILDING_TYPE: {
                gameControler->locateBuildingAt(event.player_id, event.picturable_id, event.release_position);
                break;
            }
            case SELL_TYPE: {
                gameControler->sell(event.player_id);
                break;
            }
            default:
                break;
        }
    }
}

void Game::updateClients() {
    std::vector<Picturable> state;
    std::pair<GameStatusEvent, bool> player_state;
    GameStatusEvent statusEvent;
    bool player_lost;
    for (auto it = clients.begin(); it != clients.end();) {
        player_state = gameControler->getStateFor(it->first);
        statusEvent = player_state.first;
        player_lost = player_state.second;
        try {
            it->second->send(NotificationEvent(GAME_STATUS_EVENT));
            it->second->send(statusEvent);
            if (player_lost) {
                it->second->send(NotificationEvent(GAME_LOST));
                it = clients.erase(it);
            } else {
                ++it;
            }
        } catch (const SOException& e) {
            ++it;
        }
    }
    if (clients.size() == 1) {
        clients.begin()->second->send(NotificationEvent(GAME_WON));
        is_on = false;
    }
}

void Game::stop() {
    is_on = false;
}

Game::~Game() {
    delete gameControler;
}
