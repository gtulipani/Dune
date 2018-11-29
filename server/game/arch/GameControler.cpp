#include "GameControler.h"

#include <TileUtils.h>
#include <stdexcept>

#include <UnitsAndBuildings.h>

#include "../model/Map.h"
#include "../model/GameObject.h"
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
        Building* constructionCenter = gameConfig.getBuilding(*players.at(i), next_id, {}, CONSTRUCTION_CENTER);
        constructionCenter->locateAt(constructionCenterPosition, map);
        gameObjects[next_id] = constructionCenter;
        next_id++;
        std::vector<Point> initPoss = map.getAvailableTilesNear(tile_utils::getTileFromPixel(constructionCenterPosition), 5);
        for (int j = 0; j < 2; j++) {
            Point pos = tile_utils::getTileTopLeft(initPoss.at(j));
            auto * cosechadora = gameConfig.getCosechadora(*players.at(i), next_id, pos, map);
            gameObjects[next_id] = cosechadora;
            next_id++;
        }
        for (int j = 2; j < 5; j++) {
            Point pos = tile_utils::getTileTopLeft(initPoss.at(j));
            auto * trike = gameConfig.getVehiculo(*players.at(i), next_id, pos, map, TRIKE);
            gameObjects[next_id] = trike;
            next_id++;
        }
    }
}

void GameControler::initialize(int number_of_players) {
    initializePlayers(number_of_players);
    especias = map.generateEspeciaFromId(next_id);
}

void GameControler::tick() {
    for (auto& gameObject : gameObjects) {
        // We let know all the objects that time has passed
        gameObject.second->tick();
    }
    for (auto& inProgressUnit : inProgressUnits) {
        inProgressUnit.second->tick();
    }
    for (auto& inProgressBuilding : inProgressBuildings) {
        inProgressBuilding.second->tick();
    }
}

void GameControler::leftClick(int player_id, const Point& point) {
    std::map<int, SelectableGameObject*>& selectedObjects = players.at(player_id)->selectedObjects;
    if (!selectedObjects.empty()) {
        for (auto& selectedObject : selectedObjects) {
            selectedObject.second->unselect();
        }
        players.at(player_id)->changedSelection = true;
        selectedObjects.clear();
    }

    for (auto& gameObject : gameObjects) {
        bool success = gameObject.second->tryToSelect(point);
        if (success) {
            selectedObjects[gameObject.first] = gameObject.second;
            break;
        }
    }
    if (!players.at(player_id)->changedSelection && !selectedObjects.empty()) {
        players.at(player_id)->changedSelection = true;
    }
}

void GameControler::rightClick(int player_id, const Point& point) {
    SelectableGameObject* unit_at_pos = nullptr;
    for (auto& gameObject : gameObjects) {
        if (gameObject.second->isThere(point)) {
            unit_at_pos = gameObject.second;
            break;
        }
    }
    
    std::map<int, SelectableGameObject*>& selectedObjects = players.at(player_id)->selectedObjects;
    for (auto& selectedObject : selectedObjects) {
        if (unit_at_pos != nullptr && unit_at_pos->isEnemy(selectedObject.second)) {
            ((AttackingUnit*)(selectedObject.second))->attack(unit_at_pos);
        } else {
            if (selectedObject.second->player == *players.at(player_id)) {
                selectedObject.second->handleRightClick(point);
            }
        }
    }
}

void GameControler::createVehiculo(int player_id, const std::string& unitName) {
    auto* unit = gameConfig.getVehiculo(*players.at(player_id), next_id, {}, map, unitName);
    auto* unitInProgress = new InProgressGameObject(unit, gameConfig.getTiempoUnit(unitName));
    inProgressUnits[next_id] = unitInProgress;
    next_id++;
}

void GameControler::createInfanteria(int player_id, const std::string& unitName) {
    auto* unit = gameConfig.getInfanteria(*players.at(player_id), next_id, {}, map, unitName);
    auto* unitInProgress = new InProgressGameObject(unit, gameConfig.getTiempoUnit(unitName));
    inProgressUnits[next_id] = unitInProgress;
    next_id++;
}

void GameControler::createBuilding(int player_id, const std::string& buildingName) {
    auto* building = gameConfig.getBuilding(*players.at(player_id), next_id, {}, buildingName);
    auto* buildingInProgress = new InProgressGameObject(building, gameConfig.getTiempoBuilding(buildingName));
    inProgressBuildings[next_id] = buildingInProgress;
    next_id++;
}

void GameControler::locateBuildingAt(int id, const Point& pos) {
    if (inProgressBuildings.at(id)->completed()) {
        Building* building = (Building*)inProgressBuildings.at(id)->getObject();
        delete inProgressBuildings.at(id);
        inProgressBuildings.erase(id);
        building->locateAt(pos, map);
        gameObjects[id] = building;
    }
}

void GameControler::createCosechadora(int player_id) {
    auto * cosechadora = gameConfig.getCosechadora(*players.at(player_id), next_id, {}, map);
    auto * cosechadoraInProgress = new InProgressGameObject(cosechadora, gameConfig.getTiempoUnit(HARVESTER));
    inProgressUnits[next_id] = cosechadoraInProgress;
    next_id++;
}

std::vector<Picturable> GameControler::getStateFor(int player_id) {
    Player& player = *players.at(player_id);
    std::vector<Picturable> state;

    for (const auto& gameObject : gameObjects) {
        bool playerChangedSelection = player.changedSelection;
        bool currentIsOnSelection = false;
        try {
            player.selectedObjects.at(gameObject.first);
            currentIsOnSelection = true;
        } catch (const std::out_of_range& e) {}
        if (gameObject.second->haveYouChanged() || (playerChangedSelection && currentIsOnSelection)) {
            Picturable currentState = gameObject.second->getState();
            currentState.selected = currentIsOnSelection;
            state.push_back(currentState);
        }
    }
    for (const auto& gameObject : inProgressUnits) {
        if (gameObject.second->haveYouChanged()) {
            state.push_back(gameObject.second->getState());
        }
    }
    for (const auto& gameObject : inProgressBuildings) {
        if (gameObject.second->haveYouChanged()) {
            state.push_back(gameObject.second->getState());
        }
    }
    for (const auto& especia : especias) {
        if (especia.second->haveYouChanged()) {
            state.push_back(*especia.second);
        }
    }

    return state;
}

void GameControler::updateGameObjects() {
    for (auto it = gameObjects.begin(); it != gameObjects.end();) {
        if (it->second->isDead()) {
            delete it->second;
            it = gameObjects.erase(it);
        } else {
            ++it;
        }
    }

    for (auto it = inProgressUnits.begin(); it != inProgressUnits.end();) {
        if (it->second->completed()) {
            gameObjects[it->first] = it->second->getObject();
            delete it->second;
            it = inProgressUnits.erase(it);
        } else {
            ++it;
        }
    }

    for (auto it = especias.begin(); it != especias.end();) {
        if (it->second->runOut()) {
            delete it->second;
            it = especias.erase(it);
        } else {
            ++it;
        }
    }

    for (const auto& gameObject : gameObjects) {
        gameObject.second->reset();
    }
    for (const auto& gameObject : inProgressUnits) {
        gameObject.second->reset();
    }
    for (const auto& gameObject : inProgressBuildings) {
        gameObject.second->reset();
    }
    for (const auto& especia : especias) {
        especia.second->reset();
    }
    for (const auto& player : players) {
        player.second->changedSelection = false;
    }
}

GameControler::~GameControler() {
    for (const auto& gameObject : gameObjects) {
        delete gameObject.second;
    }
    for (const auto& player : players) {
        delete player.second;
    }
}
