#include "GameObject.h"

GameObject::GameObject(int _id, int _sprite) {
    id = _id;
    sprite = _sprite;
}

Picturable GameObject::getState() const {
    return {id, type, sprite, selected, pixelPosition, health};
}

void GameObject::select() {
    selected = true;
}

void GameObject::unselect() {
    selected = false;
}