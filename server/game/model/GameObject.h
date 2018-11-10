#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <string>
#include <Picturable.h>

class GameObject {
    protected:
    int id;
    int type;
    int sprite;
    int health;
    bool selected;
    Point pixelPosition;

    public:
    GameObject(int _id, int _sprite);

    virtual void tick() = 0;

    virtual void handleRightClick(const Point& pos) = 0;

    virtual bool haveYouChanged() const = 0;

    virtual Picturable getState() const;

    void select();

    void unselect();
};

#endif
