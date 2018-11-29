#include "GameControler.h"

#include <TileUtils.h>
#include <stdexcept>

#include <UnitsAndBuildings.h>

#include <events/GameStatusEvent.h>

#include "../model/Map.h"
#include "../model/GameObject.h"
#include "../model/SelectableGameObject.h"
#include "../model/WalkingUnit.h"
#include "../model/AttackingUnit.h"
#include "../model/Cosechadora.h"
#include "../model/Vehiculo.h"
#include "../model/Infanteria.h"
#include "../model/Especia.h"
#include "../model/Building.h"
#include "../model/InProgressGameObject.h"

GameControler::GameControler(Map& map, const GameConfiguration& gameConfig) :
 map(map), gameConfig(gameConfig) {}

const int CONSTRUCTION_CENTER_HEALTH = 1000;
const Point CONSTRUCTION_CENTER_SIZE = {3 * TILE_PIXEL_RATE, 3 * TILE_PIXEL_RATE};

void GameControler::initializePlayers(int number_of_players) {
    for (int i = 0; i < number_of_players; i++) {
        Point constructionCenterPosition = tile_utils::getTileTopLeft(map.constructionCenterPositions.at(i));
        players[i] = new Player(i);
        Building* constructionCenter = gameConfig.getBuilding(*players.at(i), next_id, CONSTRUCTION_CENTER);
        constructionCenter->locateAt(constructionCenterPosition, map);
        players.at(i)->buildings[next_id] = constructionCenter;
        players.at(i)->buildingsOwnedNames.insert(CONSTRUCTION_CENTER);
        next_id++;

        std::vector<Point> initPoss = map.getAvailableTilesNear(tile_utils::getTileFromPixel(constructionCenterPosition), 5);
        for (int j = 0; j < 2; j++) {
            Point pos = tile_utils::getTileTopLeft(initPoss.at(j));
            auto * cosechadora = gameConfig.getCosechadora(*players.at(i), next_id, pos, map);
            players.at(i)->units[next_id] = cosechadora;
            next_id++;
        }
        for (int j = 2; j < 5; j++) {
            Point pos = tile_utils::getTileTopLeft(initPoss.at(j));
            auto * trike = gameConfig.getVehiculo(*players.at(i), next_id, pos, map, TRIKE);
            players.at(i)->units[next_id] = trike;
            next_id++;
        }
    }
}

void GameControler::initialize(int number_of_players) {
    initializePlayers(number_of_players);
    especias = map.generateEspeciaFromId(next_id);
}

void GameControler::tick() {
    for (auto& player : players) {
        for (auto& unit : player.second->units) {
            unit.second->tick();
        }
        for (auto& building : player.second->buildings) {
            building.second->tick();
        }
        for (auto& inProgressUnit : player.second->inProgressUnits) {
            inProgressUnit.second->tick();
        }
        for (auto& inProgressBuilding : player.second->inProgressBuildings) {
            inProgressBuilding.second->tick();
        }
    }
}

void GameControler::leftClick(int player_id, const Point& point) {
    // First clear current selection
    std::map<int, SelectableGameObject*>& selectedObjects = players.at(player_id)->selectedObjects;
    if (!selectedObjects.empty()) {
        players.at(player_id)->changedSelection = true;
    }
    for (auto& selectedObject : selectedObjects) {
        selectedObject.second->unselect();
    }
    selectedObjects.clear();

    bool success = false;

    // Now we try to select every unit of the game.
    // Priority is player units.
    for (auto& unit : players.at(player_id)->units) {
        if (unit.second->isThere(point)) {
            unit.second->select();
            selectedObjects[unit.first] = unit.second;
            success = true;
            break;
        }
    }
    if (!success) {
        // Then his buildings
        for (auto& building : players.at(player_id)->buildings) {
            if (building.second->isThere(point)) {
                building.second->select();
                selectedObjects[building.first] = building.second;
                success = true;
                break;
            }
        }
        if (!success) {
            // Then the rest of the units
            for (auto& player : players) {
                if (player.second->id == player_id) continue;
                for (auto& unit : player.second->units) {
                    if (unit.second->isThere(point)) {
                        unit.second->select();
                        selectedObjects[unit.first] = unit.second;
                        success = true;
                        break;
                    }
                }
            }
            if (!success) {
                // Finally the rest of the buildings
                for (auto& player : players) {
                    if (player.second->id == player_id) continue;
                    for (auto& building : player.second->buildings) {
                        if (building.second->isThere(point)) {
                            building.second->select();
                            selectedObjects[building.first] = building.second;
                            success = true;
                            break;
                        }
                    }
                }
            }
        }
    }

    if (!players.at(player_id)->changedSelection && !selectedObjects.empty()) {
        players.at(player_id)->changedSelection = true;
    }
}

void GameControler::rightClick(int player_id, const Point& point) {
    SelectableGameObject* object_at_pos = nullptr;
    
    // Priority is enemy units
    for (auto& player : players) {
        if (player.second->id == player_id) continue;
        for (auto& unit : player.second->units) {
            if (unit.second->isThere(point)) {
                object_at_pos = unit.second;
                break;
            }
        }
    }
    if (object_at_pos == nullptr) {
        // Then enemy buildings
        for (auto& player : players) {
            if (player.second->id == player_id) continue;
            for (auto& building : player.second->buildings) {
                if (building.second->isThere(point)) {
                    object_at_pos = building.second;
                    break;
                }
            }
        }
    }

    std::map<int, SelectableGameObject*>& selectedObjects = players.at(player_id)->selectedObjects;
    
    // If none was there, we tell selected object of player to walk there
    if (object_at_pos == nullptr) {
        for (auto& selectedObject : selectedObjects) {
            // Only if the unit belongs to the player
            if (selectedObject.second->player == *players.at(player_id)) {
                selectedObject.second->handleRightClick(point);
            }
        }
    // Else, we tell all selected objects of player to attack it
    } else {
        for (auto& selectedObject : selectedObjects) {
            // Only if they are enemies
            selectedObject.second->attack(object_at_pos);
        }
    }
}

void GameControler::createVehiculo(int player_id, const std::string& unitName) {
    auto* unit = gameConfig.getVehiculo(*players.at(player_id), next_id, {}, map, unitName);
    auto* unitInProgress = new InProgressGameObject(unit, gameConfig.getTiempoUnit(unitName));
    players.at(player_id)->inProgressUnits[next_id] = unitInProgress;
    next_id++;
}

void GameControler::createInfanteria(int player_id, const std::string& unitName) {
    auto* unit = gameConfig.getInfanteria(*players.at(player_id), next_id, {}, map, unitName);
    auto* unitInProgress = new InProgressGameObject(unit, gameConfig.getTiempoUnit(unitName));
    players.at(player_id)->inProgressUnits[next_id] = unitInProgress;
    next_id++;
}

void GameControler::createBuilding(int player_id, const std::string& buildingName) {
    auto* building = gameConfig.getBuilding(*players.at(player_id), next_id, buildingName);
    auto* buildingInProgress = new InProgressGameObject(building, gameConfig.getTiempoBuilding(buildingName));
    players.at(player_id)->inProgressBuildings[next_id] = buildingInProgress;
    next_id++;
}

void GameControler::locateBuildingAt(int player_id, int building_id, const Point& pos) {
    if (players.at(player_id)->inProgressBuildings.at(building_id)->completed()) {
        Building* building = (Building*)players.at(player_id)->inProgressBuildings.at(building_id)->getObject();
        delete players.at(player_id)->inProgressBuildings.at(building_id);
        players.at(player_id)->inProgressBuildings.erase(building_id);
        building->locateAt(pos, map);
        players.at(player_id)->buildings[building_id] = building;
        players.at(player_id)->buildingsOwnedNames.insert(building->getName());
    }
}

void GameControler::createCosechadora(int player_id) {
    auto* cosechadora = gameConfig.getCosechadora(*players.at(player_id), next_id, {}, map);
    auto* cosechadoraInProgress = new InProgressGameObject(cosechadora, gameConfig.getTiempoUnit(HARVESTER));
    players.at(player_id)->inProgressUnits[next_id] = cosechadoraInProgress;
    next_id++;
}

GameStatusEvent GameControler::getStateFor(int player_id) const {
    GameStatusEvent playerState;

    if (players.at(player_id)->changedSelection) {
        for (const auto& selectedObject : players.at(player_id)->selectedObjects) {
            playerState.selectedObjects.push_back(selectedObject.second->getState());
        }
    }

    for (const auto& player : players) {
        for (const auto& unit : player.second->units) {
            if (unit.second->haveYouChanged()) {
                playerState.picturables.push_back(unit.second->getState());
            }
        }
        for (const auto& building : player.second->buildings) {
            if (building.second->haveYouChanged()) {
                playerState.picturables.push_back(building.second->getState());
            }
        }
        for (const auto& inProgressUnit : player.second->inProgressUnits) {
            if (inProgressUnit.second->haveYouChanged()) {
                playerState.picturables.push_back(inProgressUnit.second->getState());
            }
        }
        for (const auto& inProgressBuilding : player.second->inProgressBuildings) {
            if (inProgressBuilding.second->haveYouChanged()) {
                playerState.picturables.push_back(inProgressBuilding.second->getState());
            }
        }
    }
    for (const auto& especia : especias) {
        if (especia.second->haveYouChanged()) {
            playerState.picturables.push_back(*especia.second);
        }
    }
    playerState.especia = players.at(player_id)->especia;
    playerState.energia = players.at(player_id)->energia;
    playerState.availableObjects = gameConfig.getAvailableObjectsFor(*players.at((player_id)));
    for (auto& selectedObject : players.at(player_id)->selectedObjects) {
        playerState.selectedObjects.push_back(selectedObject.second->getState());
    }

    return playerState;
}

void GameControler::updateGameObjects() {
    for (const auto& player : players) {
        for (auto it = player.second->units.begin(); it != player.second->units.end();) {
            if (it->second->isDead()) {
                delete it->second;
                it = player.second->units.erase(it);
            } else {
                it->second->reset();
                ++it;
            }
        }
        for (auto it = player.second->buildings.begin(); it != player.second->buildings.end();) {
            if (it->second->isDead()) {
                delete it->second;
                it = player.second->buildings.erase(it);
            } else {
                it->second->reset();
                ++it;
            }
        }
        for (auto it = player.second->inProgressUnits.begin(); it != player.second->inProgressUnits.end();) {
            if (it->second->completed()) {
                player.second->units[it->first] = (WalkingUnit*)it->second->getObject();
                delete it->second;
                it = player.second->inProgressUnits.erase(it);
            } else {
                it->second->reset();
                ++it;
            }
        }
        for (auto it = player.second->inProgressBuildings.begin(); it != player.second->inProgressBuildings.end();) {
            if (it->second->completed()) {
                player.second->buildings[it->first] = (Building*)it->second->getObject();
                delete it->second;
                it = player.second->inProgressBuildings.erase(it);
            } else {
                it->second->reset();
                ++it;
            }
        }
    }

    for (auto it = especias.begin(); it != especias.end();) {
        if (it->second->runOut()) {
            delete it->second;
            it = especias.erase(it);
        } else {
            it->second->reset();
            ++it;
        }
    }

    for (const auto& player : players) {
        player.second->changedSelection = false;
    }
}

GameControler::~GameControler() {
    for (const auto& player : players) {
        for (auto& unit : player.second->units) {
            delete unit.second;
        }
        for (auto& building : player.second->buildings) {
            delete building.second;
        }
        for (auto& inProgressUnit : player.second->inProgressUnits) {
            delete inProgressUnit.second;
        }
        for (auto& inProgressbuilding : player.second->inProgressBuildings) {
            delete inProgressbuilding.second;
        }
        delete player.second;
    }
    for (auto& especia : especias) {
        delete especia.second;
    }
}
