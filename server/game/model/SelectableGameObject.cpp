#include "SelectableGameObject.h"

#include "Player.h"

SelectableGameObject::SelectableGameObject(Player& player, int id, int type, int health, const Point& size, const Point& initialPixelPosition) :
AliveGameObject(player, id, type, health), size(size), pixelPosition(initialPixelPosition) {}

bool SelectableGameObject::isThere(const Point& pos) const {
    int diffRow = pos.row - pixelPosition.row;
    int diffCol = pos.col - pixelPosition.col;
    return diffRow >= 0 && diffCol >= 0 && diffRow <= size.row && diffCol <= size.col;
}

void SelectableGameObject::select() {
    selected = true;
    //haveIChanged = true;
}

Point SelectableGameObject::getPixelPosition() const {
    return pixelPosition;
}

void SelectableGameObject::unselect() {
    selected = false;
    //haveIChanged = true;
}

void SelectableGameObject::attack(SelectableGameObject* target) {}

void SelectableGameObject::recieveAttack(AttackingUnit* enemy, int attackPoints) {
    health -= attackPoints;
    haveIChanged = true;
}

Picturable SelectableGameObject::getState() const {
    return {player.id, id, type, sprite_direction, sprite_motion, selected, pixelPosition, size, health, max_health, 100};
}
