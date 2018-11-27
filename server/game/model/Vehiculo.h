#ifndef __VEHICULO_H__
#define __VEHICULO_H__

#include "AttackingUnit.h"

class Vehiculo : public AttackingUnit {
    public:
    Vehiculo(Player& player, int id, Sprites sprite, int health, const Point& size,
                const Point& initialPixelPosition, Map& map, unsigned int movespeed,
                const Weapon& weapon, unsigned int range);
    
    virtual void filterBadTiles(std::vector<Point> &tiles) const override;
};

#endif
