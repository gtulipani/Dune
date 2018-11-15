#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <string>
#include <Picturable.h>

class GameObject {
    protected:
    int id;
    Point size;
    Point pixelPosition;
    const int type = 0;
    int motion = 0;
    bool selected = false;
    int health = 500;
    bool haveIChanged = true;

    public:
    GameObject(int _id, const Point& _size, const Point& initialPosition);

    virtual void tick() = 0;

    virtual void handleRightClick(const Point& pos) = 0;

    bool tryToSelect(const Point& pos);

    void unselect();

    virtual bool haveYouChanged() const = 0;

    virtual Picturable getState();

    virtual ~GameObject() = default;
};

#endif
