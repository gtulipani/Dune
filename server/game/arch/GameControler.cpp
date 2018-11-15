#include "GameControler.h"

#include <TileUtils.h>

#include "../model/Map.h"
#include "../model/GameObject.h"
#include "../model/WalkingUnit.h"
#include "../model/Building.h"

GameControler::GameControler(std::list<GameObject*>& _gameObjects, Map& _map) :
gameObjects(_gameObjects), map(_map) {}

void GameControler::initializeMap() {
    for (Point tilePosition : map.constructionCenterPositions) {
        Point pixelPosition = tile_utils::getTileTopLeft(tilePosition);
        GameObject* constructionCenter = new Building(gameObjects.size(), Point(TILE_PIXEL_RATE * 3, TILE_PIXEL_RATE * 3), pixelPosition);
        gameObjects.push_back(constructionCenter);
        map.update(EDIFICIOS, Point(3, 3), tilePosition);
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
    auto * unit = new WalkingUnit(gameObjects.size(), {32, 32}, point, map, 10);
    gameObjects.push_back(unit);
}
