#ifndef __ALIVE_GAME_OBJECT_H__
#define __ALIVE_GAME_OBJECT_H__

#include "GameObject.h"

class AliveGameObject : public GameObject {
    protected:
    int health;
    int max_health;

    public:
    explicit AliveGameObject(Player& player, int id, Sprites sprite, int health);

    bool isDead() const;

    void kill();

    virtual ~AliveGameObject() = default;
};

#endif
