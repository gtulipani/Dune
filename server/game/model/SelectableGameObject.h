#ifndef __SELECTABLE_GAME_OBJECT_H__
#define __SELECTABLE_GAME_OBJECT_H__

#include "AliveGameObject.h"

class AttackingUnit;

class SelectableGameObject : public AliveGameObject {
    private:
    bool selected = false;
    
    protected:
    Point size;
    Point pixelPosition;
    int sprite_motion = 0;
    Direction sprite_direction = SPRITE_DOWN;

    public:
    SelectableGameObject(Player& player, int id, int type, int health, const Point& size, const Point& initialPixelPosition);

    virtual void handleRightClick(const Point& pos) = 0;

    Point getPixelPosition() const;

    bool isThere(const Point& pos) const;

    bool tryToSelect(const Point& clickPosition);

    void unselect();

    virtual void recieveAttack(AttackingUnit* enemy, int attackPoints);

    virtual Picturable getState() const override;

    virtual ~SelectableGameObject() = default;
};

#endif
