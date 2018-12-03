#include "AttackingUnit.h"

#include <Tick.h>
#include <TileUtils.h>
#include "Weapon.h"
#include "Map.h"

AttackingUnit::AttackingUnit(Player& player, int id, const std::string& name, int health,
                            const Point& size, const Point& initialPixelPosition,
                            Map& map, int movespeed, const Weapon& weapon,
                            int range) :
WalkingUnit(player, id, name, health, size, initialPixelPosition, map, movespeed) ,
weapon(weapon), range(TILE_PIXEL_RATE * range) {}

bool AttackingUnit::inRange(const Point& pos) const {
    return (int)::abs(pos.row - pixelPosition.row) <= range && (int)::abs(pos.col - pixelPosition.col) <= range;
}

void AttackingUnit::attack(SelectableGameObject* enemy) {
    target = enemy;
    targetPos = target->getPixelPosition();
    if (!inRange(targetPos)) {
        Point whereToGo = map.getClosestAvailablePoint(pixelPosition, targetPos);
        this->WalkingUnit::handleRightClick(whereToGo);
    }
}

void AttackingUnit::tick() {
    if (target == nullptr) {
        this->WalkingUnit::tick();
        return;
    }

    Point currentTargetPos = target->getPixelPosition();

    if (inRange(currentTargetPos)) {
        std::stack<Point> empty_stack;
        path = empty_stack;
        pixelGoal = pixelPosition;
        
        if (GameObject::checkCounter(counter, TO_TICKS(weapon.shot_frequency))) {
            target->recieveAttack(this, weapon.damage);
            if (target->isDead()) target = nullptr;
        }
    } else {
        if (currentTargetPos != targetPos) {
            targetPos = currentTargetPos;
            Point whereToGo = map.getClosestAvailablePoint(pixelPosition, targetPos);
            this->WalkingUnit::handleRightClick(whereToGo);
        }
        this->WalkingUnit::tick();
    }
}

void AttackingUnit::recieveAttack(AttackingUnit* enemy, int attackPoints) {
    if (enemy->isDead()) return;
    if (target == nullptr) {
        this->attack(enemy);
    }
    this->SelectableGameObject::recieveAttack(enemy, attackPoints);
}
