#include "EventsHandler.h"

#include "../model/Map.h"
#include "../model/GameObject.h"
#include "../model/WalkingUnit.h"

EventsHandler::EventsHandler(std::list<GameObject*>& _gameObjects, Map& _map) :
gameObjects(_gameObjects), map(_map) {}

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
    auto * unit = new WalkingUnit(0, {32, 32}, point, map, 10);
    gameObjects.push_back(unit);
}
