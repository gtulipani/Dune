#include "Vehiculo.h"

#include "TerrainType.h"
#include "Map.h"

Vehiculo::Vehiculo(Player& player, int id, const std::string& name, int health, const Point& size,
const Point& initialPixelPosition, Map& map, int movespeed, const Weapon& weapon,
int range) :
AttackingUnit(player, id, name, health, size, initialPixelPosition, map, movespeed, weapon, range) {}

void Vehiculo::filterBadTiles(std::vector<Point> &tiles) const {
    for (auto it = tiles.begin(); it != tiles.end();) {
        if (map.mat.at(*it) == CIMAS || map.mat.at(*it) == PRECIPICIOS || map.mat.at(*it) == EDIFICIOS) {
            it = tiles.erase(it);
        } else {
            ++it;
        }
    }
}

void Vehiculo::nextMotion() {}