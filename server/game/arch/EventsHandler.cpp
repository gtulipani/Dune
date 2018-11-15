#include "EventsHandler.h"

#include "../model/Terrain.h"
#include "../model/GameObject.h"
#include "../model/WalkingUnit.h"

EventsHandler::EventsHandler(std::list<GameObject*>& _gameObjects, Terrain& _terrain) :
gameObjects(_gameObjects), terrain(_terrain) {}

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
    auto * unit = new WalkingUnit(0, {32, 32}, point, terrain, 10);
    gameObjects.push_back(unit);
}
