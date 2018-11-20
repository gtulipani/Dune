#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <string>
#include <Picturable.h>
#include <Sprites.h>

class Player;

class GameObject {
    protected:
    Player& player;
    const int id;
    Point size;
    Point pixelPosition;
    Sprites sprite = CONSTRUCTION_CENTER;
    bool haveIChanged = true;
    int health = 500;
    bool selected = false;

    static bool checkCounter(unsigned int& counter, unsigned int max) {
        if (counter == 0) {
            return true;
        }
        counter = counter >= max ? 0 : counter + 1;
        return false;
    }

    public:
    GameObject(Player& _player, int _id, const Point& _size, const Point& initialPosition);

    virtual void tick() = 0;

    virtual void handleRightClick(Player& player, const Point& pos) = 0;

    bool tryToSelect(const Point& clickPosition);

    void unselect();

    bool haveYouChanged() const;

    virtual Picturable getState();

    bool isDead() const;

    virtual ~GameObject() = default;
};

#endif
