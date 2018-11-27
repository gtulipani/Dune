#ifndef __INFANTERIA_H__
#define __INFANTERIA_H__

#include "AttackingUnit.h"

class Infanteria : public AttackingUnit {
    public:
    Infanteria(Player& player, int id, Sprites sprite, int health, const Point& size, const Point& initialPixelPosition,
                Map& map, unsigned int movespeed, const Weapon& weapon, unsigned int range);

    virtual void filterBadTiles(std::vector<Point> &tiles) const override;
};

#endif
