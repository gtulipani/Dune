#include "GameObject.h"

#include "Player.h"

GameObject::GameObject(Player& player, int id, Sprites sprite) :
player(player), id(id), sprite(sprite) {}

Picturable GameObject::getState() const {
    return {player.id, id, sprite, false, {0, 0}, {0, 0}, 0, 0, 100};
}

bool GameObject::haveYouChanged() const {
    return haveIChanged;
}

void GameObject::reset() {
    haveIChanged = false;
}
