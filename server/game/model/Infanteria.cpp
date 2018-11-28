#include "Infanteria.h"

#include "TerrainType.h"
#include "Map.h"

Infanteria::Infanteria(Player& player, int id, Sprites sprite, int health, const Point& size,
const Point& initialPixelPosition, Map& map, int movespeed, const Weapon& weapon,
int range) :
AttackingUnit(player, id, sprite, health, size, initialPixelPosition, map, movespeed, weapon, range) {}


void Infanteria::filterBadTiles(std::vector<Point> &tiles) const {
    for (auto it = tiles.begin(); it != tiles.end();) {
        if (map.mat.at(*it) == PRECIPICIOS || map.mat.at(*it) == EDIFICIOS) {
            it = tiles.erase(it);
        } else {
            ++it;
        }
    }
}

void Infanteria::nextMotion() {
    GameObject::checkCounter(sprite_motion, MAX_MOTION);
}
