#ifndef __ATTACKING_UNIT_H__
#define __ATTACKING_UNIT_H__

#include "WalkingUnit.h"

class AttackingUnit : public WalkingUnit {
    private:
    unsigned int ticks_per_attack;
    unsigned int range;
    unsigned int counter = 0;
    unsigned int attackPoints;
    SelectableGameObject* target = nullptr;

    bool inRange(const Point& pos) const;

    public:
    AttackingUnit(Player& player, int id, Sprites sprite, int health, const Point& size, const Point& initialPixelPosition,
                Map& map, unsigned int movespeed, unsigned int attackspeed,
                unsigned int range, unsigned int attackPoints);

    void attack(SelectableGameObject* enemy);

    virtual void recieveAttack(AttackingUnit* enemy, unsigned int attackPoints) override;

    virtual void tick() override;
};

#endif
