#include "GameObject.h"

GameObject::GameObject(Player& _player, int _id, const Point& _size, const Point& initialPosition) :
player(_player), id(_id) {
    size = _size;
    pixelPosition = initialPosition;
}

Picturable GameObject::getState() {
    haveIChanged = false;
    return {id, sprite, selected, pixelPosition, health};
}

bool GameObject::tryToSelect(const Point& clickPosition) {
    int diffRow = clickPosition.row - pixelPosition.row;
    int diffCol = clickPosition.col - pixelPosition.col;
    if (diffRow >= 0 && diffCol >= 0 && diffRow <= size.row && diffCol <= size.col) {
        haveIChanged = true;
        selected = true;
        return true;
    }
    return false;
}

void GameObject::unselect() {
    haveIChanged = true;
    selected = false;
}

bool GameObject::haveYouChanged() const {
    return haveIChanged;
}

bool GameObject::isDead() const {
    return health == 0;
}
