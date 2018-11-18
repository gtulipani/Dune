#include "GameControler.h"

#include <TileUtils.h>

#include "../model/Map.h"
#include "../model/GameObject.h"
#include "../model/WalkingUnit.h"
#include "../model/Cosechadora.h"
#include "../model/Especia.h"
#include "../model/Building.h"

GameControler::GameControler(std::vector<GameObject*>& _gameObjects, Map& _map) :
gameObjects(_gameObjects), map(_map) {}

void GameControler::initializeMap() {
    for (Point tilePosition : map.constructionCenterPositions) {
        Point pixelPosition = tile_utils::getTileTopLeft(tilePosition);
        GameObject* constructionCenter = new Building(next_id++, Point(TILE_PIXEL_RATE * 3, TILE_PIXEL_RATE * 3), pixelPosition);
        gameObjects.push_back(constructionCenter);
        map.update(EDIFICIOS, Point(3, 3), tilePosition);
    }

    std::vector<Especia*> especias = map.generateEspeciaFromId(next_id);
    for (Especia* especia : especias) {
        gameObjects.push_back(especia);
        next_id++;
    }
}

void GameControler::leftClick(const Point& point) {
    if (selectedObject != nullptr) {
        selectedObject->unselect();
        selectedObject = nullptr;
    }
    for (GameObject* gameObject : gameObjects) {
        bool success = gameObject->tryToSelect(point);
        if (success) {
            selectedObject = gameObject;
            break;
        }
    }
}

void GameControler::rightClick(const Point& point) {
    if (selectedObject != nullptr) {
        selectedObject->handleRightClick(point);
    }
}

void GameControler::createWalkingUnit(const Point& point) {
    auto * unit = new WalkingUnit(next_id++, {32, 32}, point, map, 10);
    gameObjects.push_back(unit);
}

void GameControler::createCosechadora(const Point& point) {
    auto * unit = new Cosechadora(next_id++, point, map);
    gameObjects.push_back(unit);
}

void GameControler::updateGameObjects() {
    unsigned int n = gameObjects.size();
    for (unsigned int i = 0; i < n; i++) {
        if (gameObjects.at(i)->isDead()) {
            delete gameObjects.at(i);
            gameObjects.erase(gameObjects.begin() + i);
        }
    }
}
