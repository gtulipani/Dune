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
#include "../model/SiloOrRefinery.h"
#include "../model/InProgressGameObject.h"

GameControler::GameControler(Map& map, const GameConfiguration& gameConfig) :
 map(map), gameConfig(gameConfig) {}

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
    /*
    auto* silo = gameConfig.getBuilding(*players.at(0), next_id, SILO);
    silo->locateAt({11 * 31, 31 * 32}, map);
    players.at(0)->buildings[next_id] = silo;
    players.at(0)->buildingsOwnedNames.insert(SILO);
    players.at(0)->silosAndRefineries[next_id] = (SiloOrRefinery*)silo;
    next_id++;
    */
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

void GameControler::leftClick(int player_id, const Point& a, const Point& b) {
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
        if (unit.second->isThere(a, b)) {
            unit.second->select();
            selectedObjects[unit.first] = unit.second;
            success = true;
            if (a == b) break;
        }
    }
    if (!success) {
        // Then his buildings
        for (auto& building : players.at(player_id)->buildings) {
            if (building.second->isThere(a, b)) {
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
                    if (unit.second->isThere(a, b)) {
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
                        if (building.second->isThere(a, b)) {
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
            if (unit.second->isThere(point, point)) {
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
                if (building.second->isThere(point, point)) {
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
            if (selectedObject.second->player == *players.at(player_id)) {
                selectedObject.second->attack(object_at_pos);
            }
        }
    }
}

void GameControler::createVehiculo(int player_id, const std::string& unitName) {
    std::string creationBuilding = gameConfig.getCreationBuildingFor(unitName);
    Point creationBuildingTilePos;
    for (const auto& building : players.at(player_id)->buildings) {
        if (building.second->getName() == creationBuilding) {
            creationBuildingTilePos = tile_utils::getTileFromPixel(building.second->getPixelPosition());
            break;
        }
    }

    int cost = gameConfig.getUnitCost(unitName);
    players.at(player_id)->especia -= cost;

    std::vector<Point> pos = map.getAvailableTilesNear(creationBuildingTilePos, 1);
    Point unitPos = tile_utils::getTileTopLeft(pos.back());
    auto* unit = gameConfig.getVehiculo(*players.at(player_id), next_id, unitPos, map, unitName);
    auto* unitInProgress = new InProgressGameObject(unit, gameConfig.getTiempoUnit(unitName));
    players.at(player_id)->inProgressUnits[next_id] = unitInProgress;
    next_id++;
}

void GameControler::createInfanteria(int player_id, const std::string& unitName) {
    std::string creationBuilding = gameConfig.getCreationBuildingFor(unitName);
    Point creationBuildingTilePos;
    for (const auto& building : players.at(player_id)->buildings) {
        if (building.second->getName() == creationBuilding) {
            creationBuildingTilePos = tile_utils::getTileFromPixel(building.second->getPixelPosition());
            break;
        }
    }
    
    int cost = gameConfig.getUnitCost(unitName);
    players.at(player_id)->especia -= cost;
    
    std::vector<Point> pos = map.getAvailableTilesNear(creationBuildingTilePos, 1);
    Point unitPos = tile_utils::getTileTopLeft(pos.back());
    auto* unit = gameConfig.getInfanteria(*players.at(player_id), next_id, unitPos, map, unitName);
    auto* unitInProgress = new InProgressGameObject(unit, gameConfig.getTiempoUnit(unitName));
    players.at(player_id)->inProgressUnits[next_id] = unitInProgress;
    next_id++;
}

void GameControler::createBuilding(int player_id, const std::string& buildingName) {

    std::pair<int, int> cost = gameConfig.getBuildingCost(buildingName);
    players.at(player_id)->especia -= cost.first;

    auto* building = gameConfig.getBuilding(*players.at(player_id), next_id, buildingName);
    auto* buildingInProgress = new InProgressGameObject(building, gameConfig.getTiempoBuilding(buildingName));
    players.at(player_id)->inProgressBuildings[next_id] = buildingInProgress;
    next_id++;
}

void GameControler::locateBuildingAt(int player_id, int building_id, const Point& pos) {
    Building* targetBuilding = (Building*)players.at(player_id)->inProgressBuildings.at(building_id)->getObject();
    Point buildingSize = targetBuilding->getSize();
    Point downRight = {pos.row + buildingSize.row, pos.col + buildingSize.col};

    if (!map.canIBuildAt(pos, buildingSize)) return;

    for (const auto& player : players) {
        for (const auto& unit : player.second->units) {
            if (unit.second->isThere(pos, downRight)) return;
        }
        for (const auto& building : player.second->buildings) {
            if (building.second->isThere(pos, downRight)) return;
        }
    }

    if (players.at(player_id)->inProgressBuildings.at(building_id)->completed()) {
        delete players.at(player_id)->inProgressBuildings.at(building_id);
        players.at(player_id)->inProgressBuildings.erase(building_id);
        targetBuilding->locateAt(pos, map);
        players.at(player_id)->buildings[building_id] = targetBuilding;
        players.at(player_id)->buildingsOwnedNames.insert(targetBuilding->getName());

        std::pair<int, int> cost = gameConfig.getBuildingCost(targetBuilding->getName());
        players.at(player_id)->energia -= cost.second;

        if (targetBuilding->getName() == SILO || targetBuilding->getName() == REFINERY) players.at(player_id)->silosAndRefineries[building_id] = (SiloOrRefinery*)targetBuilding;
    }
}

void GameControler::createCosechadora(int player_id) {
    std::string creationBuilding = gameConfig.getCreationBuildingFor(HARVESTER);
    Point creationBuildingTilePos;
    for (const auto& building : players.at(player_id)->buildings) {
        if (building.second->getName() == creationBuilding) {
            creationBuildingTilePos = tile_utils::getTileFromPixel(building.second->getPixelPosition());
            break;
        }
    }

    int cost = gameConfig.getUnitCost(HARVESTER);
    players.at(player_id)->especia -= cost;

    std::vector<Point> pos = map.getAvailableTilesNear(creationBuildingTilePos, 1);
    Point unitPos = tile_utils::getTileTopLeft(pos.back());
    auto* unit = gameConfig.getCosechadora(*players.at(player_id), next_id, unitPos, map);
    auto* unitInProgress = new InProgressGameObject(unit, gameConfig.getTiempoUnit(HARVESTER));
    players.at(player_id)->inProgressUnits[next_id] = unitInProgress;
    next_id++;
}

void GameControler::sell(int player_id) {
    for (auto it = players.at(player_id)->selectedObjects.begin(); it != players.at(player_id)->selectedObjects.end();) {
        if (it->second->player.id == player_id) {
            try {
                players.at(player_id)->especia += gameConfig.getUnitCost(it->second->getName()) / 2;
            } catch (const std::out_of_range& e) {
                players.at(player_id)->especia += gameConfig.getBuildingCost(it->second->getName()).second / 2;
            }
            it->second->kill();
            it = players.at(player_id)->selectedObjects.erase(it);
        } else {
            ++it;
        }
    }
}

std::pair<GameStatusEvent, bool> GameControler::getStateFor(int player_id) const {
    GameStatusEvent playerState;

    for (const auto& player : players) {
        for (const auto& unit : player.second->units) {
            if (unit.second->haveYouChanged()) {
                playerState.picturables.push_back(unit.second->getState());
                if (players.at(player_id)->selectedObjects.find(unit.first) != players.at(player_id)->selectedObjects.end()) {
                    playerState.picturables.back().selected = true;
                }
            }
        }
        for (const auto& building : player.second->buildings) {
            if (building.second->haveYouChanged()) {
                playerState.picturables.push_back(building.second->getState());
                if (players.at(player_id)->selectedObjects.find(building.first) != players.at(player_id)->selectedObjects.end()) {
                    playerState.picturables.back().selected = true;
                }
            }
        }
    }

    for (const auto& inProgressUnit : players.at(player_id)->inProgressUnits) {
        if (inProgressUnit.second->haveYouChanged()) {
            playerState.picturables.push_back(inProgressUnit.second->getState());
        }
    }
    for (const auto& inProgressBuilding : players.at(player_id)->inProgressBuildings) {
        if (inProgressBuilding.second->haveYouChanged()) {
            playerState.picturables.push_back(inProgressBuilding.second->getState());
        }
    }

    for (const auto& especia : especias) {
        if (especia.second->haveYouChanged()) {
            playerState.picturables.push_back(*especia.second);
        }
    }

    playerState.especia = players.at(player_id)->especia;
    playerState.energy = players.at(player_id)->energia;
    playerState.availableObjects = gameConfig.getAvailableObjectsFor(*players.at((player_id)));

    return {playerState, players.at(player_id)->lost};
}

void GameControler::updateGameObjects() {
    bool delete_lost_players = true;
    for (auto it_player = players.begin(); it_player != players.end();) {
        for (auto it = it_player->second->units.begin(); it != it_player->second->units.end();) {
            if (it->second->isDead()) {
                delete it->second;
                it = it_player->second->units.erase(it);
            } else {
                it->second->reset();
                ++it;
            }
        }
        for (auto it = it_player->second->buildings.begin(); it != it_player->second->buildings.end();) {
            if (it->second->isDead()) {
                if (it->second->getName() == CONSTRUCTION_CENTER) {
                    processLostPlayer(it_player->first);
                    delete_lost_players = false; // Will be deleted on the next iteration
                    break;
                }
                if (it->second->getName() == SILO || it->second->getName() == REFINERY) {
                    delete it_player->second->silosAndRefineries.at(it->first);
                    it_player->second->silosAndRefineries.erase(it->first);
                }
                delete it->second;
                it = it_player->second->buildings.erase(it);
            } else {
                it->second->reset();
                ++it;
            }
        }
        for (auto it = it_player->second->inProgressUnits.begin(); it != it_player->second->inProgressUnits.end();) {
            if (it->second->completed()) {
                it_player->second->units[it->first] = (WalkingUnit*)it->second->getObject();
                delete it->second;
                it = it_player->second->inProgressUnits.erase(it);
            } else {
                it->second->reset();
                ++it;
            }
        }
        for (auto& inProfressBuilding : it_player->second->inProgressBuildings) {
            inProfressBuilding.second->reset();
        }
        if (it_player->second->lost && delete_lost_players) {
            it_player = players.erase(it_player);
            delete it_player->second;
        } else {
            ++it_player;
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

void GameControler::processLostPlayer(int player_id) {
    players.at(player_id)->lost = true;
    for (auto& unit : players.at(player_id)->units) {
        unit.second->kill();
    }
    for (auto& building : players.at(player_id)->buildings) {
        building.second->kill();
    }
    for (auto& inProgressUnit : players.at(player_id)->inProgressUnits) {
        delete inProgressUnit.second;
    }
    players.at(player_id)->inProgressUnits.clear();
    for (auto& inProgressbuilding : players.at(player_id)->inProgressBuildings) {
        delete inProgressbuilding.second;
    }
    players.at(player_id)->inProgressBuildings.clear();
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
