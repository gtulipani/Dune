#include "Building.h"

Building::Building(Player& player, int id, Sprites sprite, int health, const Point& size, const Point& initialPixelPosition) :
SelectableGameObject(player, id, sprite, health, size, initialPixelPosition) {}

void Building::tick() {}

void Building::handleRightClick(const Point& pos) {}

void Building::locateAt(const Point& pos) {
    pixelPosition = pos;
}
