#include "Building.h"

Building::Building(int _id, const Point& _size, const Point& initialPosition) :
GameObject(_id, _size, initialPosition) {
    this->health = 1000;
    this->type = 1;
}

void Building::tick() {}

void Building::handleRightClick(const Point& pos) {}
