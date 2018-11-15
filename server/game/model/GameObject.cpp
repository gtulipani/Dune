#include "GameObject.h"

#include <PicturableType.h>

GameObject::GameObject(int _id, const Point& _size, const Point& initialPosition) {
    id = _id;
    size = _size;
    pixelPosition = initialPosition;
}

Picturable GameObject::getState() {
    haveIChanged = false;
    return {id, type, motion, selected, pixelPosition, health};
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
