#ifndef __BUILDING_H__
#define __BUILDING_H__

#include "SelectableGameObject.h"

class Map;

class Building : public SelectableGameObject {
	public:
    Building(Player& player, int id, const std::string& name, int health, const Point& size);

    virtual void tick() override;

    void locateAt(const Point& pos, Map& map);

    const std::string& getName() const;

    virtual void handleRightClick(const Point& pos) override;
};


#endif //__BUILDING_H__
