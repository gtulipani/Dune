#include "AliveGameObject.h"

#include "Player.h"

AliveGameObject::AliveGameObject(Player& player, int id, int type, int health) :
GameObject(player, id, type), health(health), max_health(health) {}

void AliveGameObject::kill() {
    health = 0;
}

bool AliveGameObject::isDead() const {
    return health <= 0;
}
