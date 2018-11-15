#include "EventsHandler.h"

#include <TileUtils.h>

#include "../model/Map.h"
#include "../model/GameObject.h"
#include "../model/WalkingUnit.h"
#include "../model/Building.h"

EventsHandler::EventsHandler(std::list<GameObject*>& _gameObjects, Map& _map) :
gameObjects(_gameObjects), map(_map) {}

void EventsHandler::initializeMap() {
    for (Point p : map.constructionCenterPositions) {
        GameObject* constructionCenter = new Building(gameObjects.size(), Point(TILE_PIXEL_RATE * 3, TILE_PIXEL_RATE * 3), p);
        gameObjects.push_back(constructionCenter);
    }
}

void EventsHandler::leftClick(const Point& point) {
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

void EventsHandler::rightClick(const Point& point) {
    if (selectedObject != nullptr) {
        selectedObject->handleRightClick(point);
    }
}

void EventsHandler::createWalkingUnit(const Point& point) {
    auto * unit = new WalkingUnit(gameObjects.size(), {32, 32}, point, map, 10);
    gameObjects.push_back(unit);
}
