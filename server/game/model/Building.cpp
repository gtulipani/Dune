#include "Building.h"

Building::Building(Player& player, int _id, const Point& _size, const Point& initialPosition) :
GameObject(player, _id, _size, initialPosition) {
    this->health = 1000;
    this->type = 1;
}

void Building::tick() {}

void Building::handleRightClick(Player& player, const Point& pos) {}
