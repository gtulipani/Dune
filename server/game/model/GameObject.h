#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <string>
#include <Picturable.h>

class GameObject {
    protected:
    int id;
    int type;
    int sprite;
    bool selected;
    Point size;
    int health;
    bool haveIChanged;
    Point pixelPosition;

    public:
    GameObject(int _id, int _sprite, Point _size);

    virtual void tick() = 0;

    virtual void handleRightClick(const Point& pos) = 0;

    bool tryToSelect(const Point& pos);

    void unselect();

    virtual bool haveYouChanged() const = 0;

    virtual Picturable getState();
};

#endif
