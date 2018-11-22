#include "AliveGameObject.h"

#include "Player.h"

AliveGameObject::AliveGameObject(Player& player, int id, Sprites sprite, int health) :
GameObject(player, id, sprite), health(health), max_health(health) {}

Picturable AliveGameObject::getState() const {
    return {player.id, id, sprite, false, {0, 0}, {0, 0}, health, max_health, 100};
}

bool AliveGameObject::isDead() const {
    return health == 0;
}
