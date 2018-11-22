#include "SelectableGameObject.h"

#include "Player.h"

SelectableGameObject::SelectableGameObject(Player& player, int id, Sprites sprite, int health, const Point& size, const Point& initialPixelPosition) :
AliveGameObject(player, id, sprite, health), size(size), pixelPosition(initialPixelPosition) {}

bool SelectableGameObject::tryToSelect(const Point& clickPosition) {
    int diffRow = clickPosition.row - pixelPosition.row;
    int diffCol = clickPosition.col - pixelPosition.col;
    if (diffRow >= 0 && diffCol >= 0 && diffRow <= size.row && diffCol <= size.col) {
        selected = true;
        haveIChanged = true;
        return true;
    }
    return false;
}

void SelectableGameObject::unselect() {
    selected = false;
    haveIChanged = true;
}

Picturable SelectableGameObject::getState() const {
    return {player.id, id, sprite, false, pixelPosition, size, health, max_health, 100};
}