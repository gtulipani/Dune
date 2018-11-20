#include "Building.h"

Building::Building(Player& player, int _id, const Point& _size) :
GameObject(player, _id, _size, Point(0, 0)) {
    this->health = 0;
    this->sprite = CONSTRUCTION_CENTER;
}

void Building::tick() {
    if (GameObject::checkCounter(counter, 5) && health < BUILDING_HEALTH) {
        health += 5;
        haveIChanged = true;
    }
}

void Building::handleRightClick(Player& player, const Point& pos) {}

void Building::finishConstruction() {
    if (health < BUILDING_HEALTH) {
        health = BUILDING_HEALTH;
        haveIChanged = true;
    }
}

void Building::locateAt(const Point& _pixelPosition) {
    pixelPosition = _pixelPosition;
    haveIChanged = true;
}
