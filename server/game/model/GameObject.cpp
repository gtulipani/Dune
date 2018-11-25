#include "GameObject.h"

#include "Player.h"

GameObject::GameObject(Player& player, int id, Sprites sprite) :
player(player), id(id), sprite(sprite) {}

bool GameObject::isEnemy(const GameObject* other) const {
    return !(other->player == player);
}

bool GameObject::haveYouChanged() const {
    return haveIChanged;
}

void GameObject::reset() {
    haveIChanged = false;
}
