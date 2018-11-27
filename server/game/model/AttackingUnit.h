#ifndef __ATTACKING_UNIT_H__
#define __ATTACKING_UNIT_H__

#include "WalkingUnit.h"

class Weapon;

class AttackingUnit : public WalkingUnit {
    private:
    unsigned int counter = 0;
    SelectableGameObject* target = nullptr;
    const Weapon& weapon;
    const unsigned int range;

    bool inRange(const Point& pos) const;

    public:
    AttackingUnit(Player& player, int id, Sprites sprite, int health, const Point& size, const Point& initialPixelPosition,
                Map& map, unsigned int movespeed, const Weapon& weapon, unsigned int range);

    void attack(SelectableGameObject* enemy);

    virtual void recieveAttack(AttackingUnit* enemy, unsigned int attackPoints) override;

    virtual void tick() override;
};

#endif
