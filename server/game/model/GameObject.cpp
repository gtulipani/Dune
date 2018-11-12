#include "GameObject.h"

#include <PicturableType.h>

GameObject::GameObject(int _id, int _sprite) {
    id = _id;
    sprite = _sprite;
    selected = false;
    haveIChanged = true;
}

Picturable GameObject::getState() {
    haveIChanged = false;
    return {id, LIGHT_INFANTRY, sprite, selected, pixelPosition, health};
}

void GameObject::select() {
    selected = true;
}

void GameObject::unselect() {
    selected = false;
}