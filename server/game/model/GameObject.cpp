#include "GameObject.h"

#include <PicturableType.h>

GameObject::GameObject(int _id, int _sprite) {
    id = _id;
    sprite = _sprite;
    selected = false;
}

Picturable GameObject::getState() const {
    return {id, LIGHT_INFANTRY, sprite, selected, pixelPosition, health};
}

void GameObject::select() {
    selected = true;
}

void GameObject::unselect() {
    selected = false;
}