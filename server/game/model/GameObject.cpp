#include "GameObject.h"

#include "Player.h"

GameObject::GameObject(Player& player, int id, const std::string& name) :
player(player), id(id), name(name) {}

bool GameObject::isEnemy(const GameObject* other) const {
    return !(other->player == player);
}

bool GameObject::haveYouChanged() const {
    return haveIChanged;
}

const std::string& GameObject::getName() const {
    return name;
}

void GameObject::reset() {
    haveIChanged = false;
}
