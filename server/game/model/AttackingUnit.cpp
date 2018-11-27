#include "AttackingUnit.h"

#include <Tick.h>
#include <TileUtils.h>
#include "Weapon.h"

AttackingUnit::AttackingUnit(Player& player, int id, Sprites sprite, int health,
                            const Point& size, const Point& initialPixelPosition,
                            Map& map, unsigned int movespeed, const Weapon& weapon,
                            unsigned int range) :
WalkingUnit(player, id, sprite, health, size, initialPixelPosition, map, movespeed) ,
weapon(weapon), range(TILE_PIXEL_RATE * range) {}

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
        if (GameObject::checkCounter(counter, TO_TICKS(weapon.shot_frequency))) {
            target->recieveAttack(this, weapon.damage);
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
