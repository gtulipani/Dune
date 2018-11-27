#include "AttackingUnit.h"

#include <Tick.h>

AttackingUnit::AttackingUnit(Player& player, int id, Sprites sprite, int health,
                            const Point& size, const Point& initialPixelPosition,
                            Map& map, unsigned int movespeed, unsigned int attackspeed,
                            unsigned int range, unsigned int attackPoints) :
WalkingUnit(player, id, sprite, health, size, initialPixelPosition, map, movespeed) ,
ticks_per_attack(TO_TICKS(attackspeed)), range(range), attackPoints(attackPoints) {}

bool AttackingUnit::inRange(const Point& pos) const {
    return (unsigned int)::abs(pos.row - pixelPosition.row) <= range && (unsigned int)::abs(pos.col - pixelPosition.col) <= range;
}

void AttackingUnit::attack(SelectableGameObject* enemy) {
    target = enemy;
}

void AttackingUnit::tick() {
    if (target == nullptr) {
        this->WalkingUnit::tick();
        return;
    }

    Point enemyPos = target->getPixelPosition();

    if (inRange(enemyPos)) {
        std::stack<Point> empty_stack;
        path = empty_stack;
        pixelGoal = pixelPosition;
        if (GameObject::checkCounter(counter, ticks_per_attack)) {
            target->recieveAttack(this, attackPoints);
            if (target->isDead()) target = nullptr;
        }
    } else {
        this->WalkingUnit::handleRightClick(enemyPos);
        this->WalkingUnit::tick();
    }
}

void AttackingUnit::recieveAttack(AttackingUnit* enemy, unsigned int attackPoints) {
    if (target == nullptr) {
        target = enemy;
    }
    this->SelectableGameObject::recieveAttack(enemy, attackPoints);
}
