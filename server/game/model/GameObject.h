#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <string>
#include <Picturable.h>
#include <Sprites.h>
#include <Point.h>

class Player;

class GameObject {
    public:
    Player& player;

    protected:
    const int id;
    std::string name;
    bool haveIChanged = true;

    public:
    static bool checkCounter(int& counter, int max) {
        bool ready = false;
        if (counter == 0) {
            ready = true;
        }
        counter = counter >= max ? 0 : counter + 1;
        return ready;
    }

    GameObject(Player& player, int id, const std::string& name);

    virtual void tick() = 0;

    bool haveYouChanged() const;

    bool isEnemy(const GameObject* other) const;

    virtual Picturable getState() const = 0;

    const std::string& getName() const;

    void reset();

    virtual ~GameObject() = default;
};

#endif
