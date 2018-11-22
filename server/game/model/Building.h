#ifndef __BUILDING_H__
#define __BUILDING_H__

#include "SelectableGameObject.h"

class Building : public SelectableGameObject {
	public:
    Building(Player& player, int id, Sprites sprite, int health, const Point& size, const Point& initialPixelPosition);

    virtual void tick() override;

    void locateAt(const Point& pos);

    virtual void handleRightClick(const Point& pos) override;
};


#endif //__BUILDING_H__
