#include "GameControler.h"

#include <TileUtils.h>
#include <stdexcept>

#include "../model/Map.h"
#include "../model/GameObject.h"
#include "../model/WalkingUnit.h"
#include "../model/AttackingUnit.h"
#include "../model/Cosechadora.h"
#include "../model/Especia.h"
#include "../model/Building.h"
#include "../model/InProgressGameObject.h"

GameControler::GameControler(Map& _map) :  map(_map) {}

const unsigned int CONSTRUCTION_CENTER_HEALTH = 1000;
const Point CONSTRUCTION_CENTER_SIZE = {3 * TILE_PIXEL_RATE, 3 * TILE_PIXEL_RATE};

void GameControler::initializePlayers(unsigned int number_of_players) {
    for (unsigned int i = 0; i < number_of_players; i++) {
        Point constructionCenterPosition = tile_utils::getTileTopLeft(map.constructionCenterPositions.at(i));
        players[i] = new Player(i);
        SelectableGameObject* constructionCenter = new Building(*players.at(i), next_id, CONSTRUCTION_CENTER, CONSTRUCTION_CENTER_HEALTH, CONSTRUCTION_CENTER_SIZE, constructionCenterPosition);
        map.update(EDIFICIOS, Point(3, 3), tile_utils::getTileFromPixel(constructionCenterPosition));
        gameObjects[next_id] = constructionCenter;
        next_id++;
        std::vector<Point> initPoss = map.getAvailableTilesNear(tile_utils::getTileFromPixel(constructionCenterPosition), 5);
        for (int j = 0; j < 2; j++) {
            Point pos = tile_utils::getTileTopLeft(initPoss.at(j));
            auto * cosechadora = new Cosechadora(*players.at(i), next_id, pos, map);
            gameObjects[next_id] = cosechadora;
            next_id++;
        }
        for (int j = 2; j < 5; j++) {
            Point pos = tile_utils::getTileTopLeft(initPoss.at(j));
            auto * trike = new AttackingUnit(*players.at(i), next_id, TRIKE_SPRITE_DOWN, 1000, {32, 32}, pos, map, 10, 5, 5, 10);
            gameObjects[next_id] = trike;
            next_id++;
        }
    }
}

void GameControler::initialize(unsigned int number_of_players) {
    initializePlayers(number_of_players);
    especias = map.generateEspeciaFromId(next_id);
}

void GameControler::tick() {
    for (auto gameObject : gameObjects) {
        // We let know all the objects that time has passed
        gameObject.second->tick();
    }
    for (auto inProgressUnit : inProgressUnits) {
        inProgressUnit.second->tick();
    }
    for (auto inProgressBuilding : inProgressBuildings) {
        inProgressBuilding.second->tick();
    }
}

void GameControler::leftClick(unsigned int player_id, const Point& point) {
    std::map<unsigned int, SelectableGameObject*>& selectedObjects = players.at(player_id)->selectedObjects;
    if (!selectedObjects.empty()) {
        for (auto selectedObject : selectedObjects) {
            selectedObject.second->unselect();
        }
        players.at(player_id)->changedSelection = true;
        selectedObjects.clear();
    }

    for (auto gameObject : gameObjects) {
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

void GameControler::rightClick(unsigned int player_id, const Point& point) {
    SelectableGameObject* unit_at_pos = nullptr;
    for (auto gameObject : gameObjects) {
        if (gameObject.second->isThere(point)) {
            unit_at_pos = gameObject.second;
            break;
        }
    }
    
    std::map<unsigned int, SelectableGameObject*>& selectedObjects = players.at(player_id)->selectedObjects;
    for (auto selectedObject : selectedObjects) {
        if (unit_at_pos != nullptr && unit_at_pos->isEnemy(selectedObject.second)) {
            ((AttackingUnit*)(selectedObject.second))->attack(unit_at_pos);
        } else {
            selectedObject.second->handleRightClick(point);
        }
    }
}

void GameControler::createTrike(unsigned int player_id) {
    auto * trike = new WalkingUnit(*players.at(player_id), next_id, TRIKE_SPRITE_DOWN, 1000, {32, 32}, {0, 0}, map, 10);
    auto * trikeInProgress = new InProgressGameObject(trike);
    inProgressUnits[next_id] = trikeInProgress;
    next_id++;
}

void GameControler::createBuilding(unsigned int player_id, const Sprites& sprite) {
    auto * building = new Building(*players.at(player_id), next_id, sprite, 1000, {32, 32}, {0, 0});
    auto * buildingInProgress = new InProgressGameObject(building);
    inProgressBuildings[next_id] = buildingInProgress;
    next_id++;
}

void GameControler::locateBuildingAt(unsigned int id, const Point& pos) {
    if (inProgressBuildings.at(id)->completed()) {
        Building* building = (Building*)inProgressBuildings.at(id)->getObject();
        delete inProgressBuildings.at(id);
        inProgressBuildings.erase(id);
        building->locateAt(pos);
        gameObjects[id] = building;
    }
}

void GameControler::createCosechadora(unsigned int player_id) {
    auto * cosechadora = new Cosechadora(*players.at(player_id), next_id, {0, 0}, map);
    auto * cosechadoraInProgress = new InProgressGameObject(cosechadora);
    inProgressUnits[next_id] = cosechadoraInProgress;
    next_id++;
}

std::vector<Picturable> GameControler::getStateFor(unsigned int player_id) {
    Player& player = *players.at(player_id);
    std::vector<Picturable> state;

    for (auto gameObject : gameObjects) {
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
    for (auto gameObject : inProgressUnits) {
        if (gameObject.second->haveYouChanged()) {
            state.push_back(gameObject.second->getState());
        }
    }
    for (auto gameObject : inProgressBuildings) {
        if (gameObject.second->haveYouChanged()) {
            state.push_back(gameObject.second->getState());
        }
    }
    for (auto especia : especias) {
        if (especia.second->haveYouChanged()) {
            state.push_back(*especia.second);
        }
    }

    return state;
}

void GameControler::updateGameObjects() {
    unsigned int n = gameObjects.size();
    for (unsigned int i = 0; i < n; i++) {
        if (gameObjects.at(i)->isDead()) {
            delete gameObjects.at(i);
            gameObjects.erase(i);
        }
    }

    std::vector<unsigned int> objectsToErase;
    for (auto inProgressUnit : inProgressUnits) {
        if (inProgressUnit.second->completed()) {
            gameObjects[inProgressUnit.first] = inProgressUnit.second->getObject();
            delete inProgressUnit.second;
            objectsToErase.push_back(inProgressUnit.first);
        }
    }
    for (unsigned int id : objectsToErase) {
        inProgressUnits.erase(id);
    }

    objectsToErase.clear();
    for (auto especia : especias) {
        if (especia.second->runOut()) {
            delete especia.second;
            objectsToErase.push_back(especia.first);
        }
    }
    for (unsigned int id : objectsToErase) {
        especias.erase(id);
    }

    for (auto gameObject : gameObjects) {
        gameObject.second->reset();
    }
    for (auto gameObject : inProgressUnits) {
        gameObject.second->reset();
    }
    for (auto gameObject : inProgressBuildings) {
        gameObject.second->reset();
    }
    for (auto especia : especias) {
        especia.second->reset();
    }

    for (auto player : players) {
        player.second->changedSelection = false;
    }
}

GameControler::~GameControler() {
    for (auto gameObject : gameObjects) {
        delete gameObject.second;
    }
    for (auto player : players) {
        delete player.second;
    }
}
