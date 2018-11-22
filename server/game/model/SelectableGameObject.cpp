#include "SelectableGameObject.h"

#include "Player.h"

SelectableGameObject::SelectableGameObject(Player& player, int id, Sprites sprite, int health, const Point& size, const Point& initialPixelPosition) :
AliveGameObject(player, id, sprite, health), size(size), pixelPosition(initialPixelPosition) {}

bool SelectableGameObject::tryToSelect(const Point& clickPosition) {
    int diffRow = clickPosition.row - pixelPosition.row;
    int diffCol = clickPosition.col - pixelPosition.col;
    if (diffRow >= 0 && diffCol >= 0 && diffRow <= size.row && diffCol <= size.col) {
        haveIChanged = true;
        selected = true;
        return true;
    }
    return false;
}

void SelectableGameObject::unselect() {
    haveIChanged = true;
    selected = false;
}

Picturable SelectableGameObject::getState() const {
    return {player.id, id, sprite, selected, pixelPosition, size, health, max_health, 100};
}