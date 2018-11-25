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

    public:
    SelectableGameObject(Player& player, int id, Sprites sprite, int health, const Point& size, const Point& initialPixelPosition);

    virtual void handleRightClick(const Point& pos) = 0;

    Point getPixelPosition() const;

    bool tryToSelect(const Point& clickPosition);

    void unselect();

    virtual void recieveAttack(AttackingUnit* enemy, unsigned int attackPoints);

    virtual Picturable getState() const override;

    virtual ~SelectableGameObject() = default;
};

#endif
