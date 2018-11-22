#include "AliveGameObject.h"

#include "Player.h"

AliveGameObject::AliveGameObject(Player& player, int id, Sprites sprite, int health) :
GameObject(player, id, sprite), health(health), max_health(health) {}

void AliveGameObject::kill() {
    health = 0;
}

bool AliveGameObject::isDead() const {
    return health == 0;
}
