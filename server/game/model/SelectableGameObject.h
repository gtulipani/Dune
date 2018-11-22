#ifndef __SELECTABLE_GAME_OBJECT_H__
#define __SELECTABLE_GAME_OBJECT_H__

#include "AliveGameObject.h"

class SelectableGameObject : public AliveGameObject {
    private:
    bool selected = false;
    
    protected:
    Point size;
    Point pixelPosition;

    public:
    SelectableGameObject(Player& player, int id, Sprites sprite, int health, const Point& size, const Point& initialPixelPosition);

    virtual void handleRightClick(const Point& pos) = 0;

    bool tryToSelect(const Point& clickPosition);

    void unselect();

    virtual Picturable getState() const override;

    virtual ~SelectableGameObject() = default;
};

#endif
