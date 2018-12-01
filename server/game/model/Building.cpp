#include "Building.h"

#include "Map.h"
#include "TileUtils.h"

Building::Building(Player& player, int id, const std::string& name, int health, const Point& size) :
SelectableGameObject(player, id, name, health, size, {}) {}

void Building::tick() {}

void Building::handleRightClick(const Point& pos) {}

void Building::locateAt(const Point& pos, Map& map) {
    pixelPosition = pos;
    map.update(EDIFICIOS, tile_utils::getTileFromPixel(size), tile_utils::getTileFromPixel(pixelPosition));
}
