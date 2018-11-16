#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <string>
#include <Picturable.h>

class GameObject {
    protected:
    const int id;
    Point size;
    Point pixelPosition;
    int type = 0;
    int motion = 0;
    bool selected = false;
    int health = 500;
    bool haveIChanged = true;

    static bool checkCounter(unsigned int& counter, unsigned int max) {
        if (counter == 0) {
            return true;
        }
        counter = counter >= max ? 0 : counter + 1;
        return false;
    }

    public:
    GameObject(int _id, const Point& _size, const Point& initialPosition);

    virtual void tick() = 0;

    virtual void handleRightClick(const Point& pos) = 0;

    bool tryToSelect(const Point& clickPosition);

    void unselect();

    bool haveYouChanged() const;

    virtual Picturable getState();

    virtual ~GameObject() = default;
};

#endif
