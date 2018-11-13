#include "GameObject.h"

#include <PicturableType.h>

GameObject::GameObject(int _id, int _sprite, Point _size) {
    id = _id;
    sprite = _sprite;
    size = _size;
    selected = false;
    haveIChanged = true;
}

Picturable GameObject::getState() {
    haveIChanged = false;
    return {id, LIGHT_INFANTRY, sprite, selected, pixelPosition, health};
}

bool GameObject::tryToSelect(const Point& pos) {
    if (pos.row - pixelPosition.row <=  size.row && pos.col - pixelPosition.col <= size.col) {
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
