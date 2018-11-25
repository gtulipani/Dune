#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <string>
#include <Picturable.h>
#include <Sprites.h>
#include <Point.h>

class Player;

class GameObject {
    protected:
    Player& player;
    const int id;
    Sprites sprite;
    bool haveIChanged = true;

    public:
    static bool checkCounter(unsigned int& counter, unsigned int max) {
        bool ready = false;
        if (counter == 0) {
            ready = true;
        }
        counter = counter >= max ? 0 : counter + 1;
        return ready;
    }

    GameObject(Player& player, int id, Sprites sprite);

    virtual void tick() = 0;

    bool haveYouChanged() const;

    bool isEnemy(const GameObject* other) const;

    virtual Picturable getState() const = 0;

    void reset();

    virtual ~GameObject() = default;
};

#endif
