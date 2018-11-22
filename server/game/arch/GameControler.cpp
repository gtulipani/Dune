#include "GameControler.h"

#include <TileUtils.h>
#include <stdexcept>

#include "../model/Map.h"
#include "../model/GameObject.h"
#include "../model/WalkingUnit.h"
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
}

void GameControler::leftClick(unsigned int player_id, const Point& point) {
    std::vector<SelectableGameObject*>& selectedObjects = players.at(player_id)->selectedObjects;
    if (!selectedObjects.empty()) {
        for (SelectableGameObject* selectedObject : selectedObjects) {
            selectedObject->unselect();
        }
        selectedObjects.clear();
    }

    for (auto gameObject : gameObjects) {
        bool success = gameObject.second->tryToSelect(point);
        if (success) {
            selectedObjects.push_back(gameObject.second);
            break;
        }
    }
}

void GameControler::rightClick(unsigned int player_id, const Point& point) {
    std::vector<SelectableGameObject*>& selectedObjects = players.at(player_id)->selectedObjects;
    for (SelectableGameObject* selectedObject : selectedObjects) {
        selectedObject->handleRightClick(point);
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

std::vector<Picturable> GameControler::getStates() {
    std::vector<Picturable> states;
    for (auto gameObject : gameObjects) {
        if (gameObject.second->haveYouChanged()) {
            states.push_back(gameObject.second->getState());
            gameObject.second->reset();
        }
    }
    for (auto gameObject : inProgressUnits) {
        if (gameObject.second->haveYouChanged()) {
            states.push_back(gameObject.second->getState());
            gameObject.second->reset();
        }
    }
    for (auto gameObject : inProgressBuildings) {
        if (gameObject.second->haveYouChanged()) {
            states.push_back(gameObject.second->getState());
            gameObject.second->reset();
        }
    }
    for (auto especia : especias) {
        if (especia.second->haveYouChanged()) {
            states.push_back(*especia.second);
            especia.second->reset();
        }
    }

    return states;
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
}

GameControler::~GameControler() {
    for (auto gameObject : gameObjects) {
        delete gameObject.second;
    }
    for (auto player : players) {
        delete player.second;
    }
}
