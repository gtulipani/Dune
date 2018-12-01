#include "SelectableGameObject.h"

#include "Player.h"

SelectableGameObject::SelectableGameObject(Player& player, int id, const std::string& name, int health, const Point& size, const Point& initialPixelPosition) :
AliveGameObject(player, id, name, health), size(size), pixelPosition(initialPixelPosition) {}

bool SelectableGameObject::isThere(const Point& a, const Point& b) const {
    Point picturableDownRight = {pixelPosition.row + size.row, pixelPosition.col + size.col};

    Point areaTopLeft;
    Point areaDownRight;
    if (a.row < b.row) {
        if (a.col < b.col) {
            areaTopLeft = a;
            areaDownRight = b;
        } else {
            areaTopLeft = {a.row, b.col};
            areaDownRight = {b.row, a.col};
        }
    } else {
        if (b.col < a.col) {
            areaTopLeft = b;
            areaDownRight = a;
        } else {
            areaTopLeft = {b.row, a.col};
            areaDownRight = {a.row, b.col};
        }
    }

    Point diff = {picturableDownRight.row - areaTopLeft.row, picturableDownRight.col - areaTopLeft.col};
    if (diff.row < 0 || diff.col < 0) return false;
    
    diff = {areaDownRight.row - pixelPosition.row, areaDownRight.col - pixelPosition.col};
    if (diff.row < 0 || diff.col < 0) return false;
    
    return true;
}
        
void SelectableGameObject::select() {
    haveIChanged = true;
}

Point SelectableGameObject::getPixelPosition() const {
    return pixelPosition;
}

void SelectableGameObject::unselect() {
    haveIChanged = true;
}

void SelectableGameObject::attack(SelectableGameObject* target) {}

void SelectableGameObject::recieveAttack(AttackingUnit* enemy, int attackPoints) {
    health -= attackPoints;
    haveIChanged = true;
}

Picturable SelectableGameObject::getState() const {
    return {player.id, id, name, sprite_direction, sprite_motion, false, pixelPosition, size, health, max_health, 100};
}

Point SelectableGameObject::getSize() const {
    return size;
}
