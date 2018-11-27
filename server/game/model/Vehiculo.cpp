#include "Vehiculo.h"

#include "TerrainType.h"
#include "Map.h"

Vehiculo::Vehiculo(Player& player, int id, Sprites sprite, int health, const Point& size,
const Point& initialPixelPosition, Map& map, unsigned int movespeed, const Weapon& weapon,
unsigned int range) :
AttackingUnit(player, id, sprite, health, size, initialPixelPosition, map, movespeed, weapon, range) {}

void Vehiculo::filterBadTiles(std::vector<Point> &tiles) const {
    for (auto it = tiles.begin(); it != tiles.end();) {
        if (map.mat.at(*it) == CIMAS || map.mat.at(*it) == PRECIPICIOS || map.mat.at(*it) == EDIFICIOS) {
            it = tiles.erase(it);
        } else {
            ++it;
        }
    }
}
